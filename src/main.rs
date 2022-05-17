//! Generate README tables of all solutions.

use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet};
use std::fmt::{self, Display};
use std::fs::{self, File};
use std::io::{self, BufRead, BufReader};
use std::path::{Path, PathBuf};
use std::str::FromStr;

/// Difficulty Levels for all site problems.
#[derive(Debug, PartialEq, Eq, PartialOrd, Ord, Hash, Clone, Copy)]
enum Difficulty {
    Easy,
    Medium,
    Hard,
    VeryHard,
}

impl Display for Difficulty {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str(match *self {
            Difficulty::Easy => "Easy",
            Difficulty::Medium => "Medium",
            Difficulty::Hard => "Hard",
            Difficulty::VeryHard => "Very Hard",
        })
    }
}

/// Parse a Difficulty enum from a string of the form:
/// "Difficulty: Easy|Medium|Hard|Very Hard|"
/// Parsing is case and spacing insensitive, and a little scuffed.
impl FromStr for Difficulty {
    type Err = ();
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let prefix = "difficulty:";
        let mut tokens = s.split_whitespace();
        let first_token = tokens.next().ok_or(())?;

        if first_token.to_lowercase() != prefix.to_lowercase() {
            return Err(());
        }

        let second_token = tokens.next().ok_or(())?;
        match second_token.to_lowercase().as_str() {
            "easy" => Ok(Difficulty::Easy),
            "medium" => Ok(Difficulty::Medium),
            "hard" => Ok(Difficulty::Hard),
            "very" => Ok(Difficulty::VeryHard),
            _ => Err(()),
        }
    }
}

/// All languages I solve problems in.
#[derive(Debug, PartialEq, Eq, PartialOrd, Ord, Hash, Clone, Copy)]
enum Language {
    Cpp,
    Rust,
    Python,
    JavaScript,
}

impl Language {
    fn from_extension(extension: &str) -> Option<Self> {
        match extension {
            "cc" | "cpp" => Some(Self::Cpp),
            "rs" => Some(Self::Rust),
            "py" => Some(Self::Python),
            "js" => Some(Self::JavaScript),
            _ => None,
        }
    }
}

impl Display for Language {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str(match *self {
            Language::Cpp => "C++",
            Language::Rust => "Rust",
            Language::Python => "Python",
            Language::JavaScript => "JavaScript",
        })
    }
}

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord, Hash, Clone, Copy)]
enum Site {
    AlgoExpert,
    LeetCode,
}

impl Display for Site {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        f.write_str(match *self {
            Site::AlgoExpert => "AlgoExpert",
            Site::LeetCode => "LeetCode",
        })
    }
}

impl FromStr for Site {
    type Err = ();
    fn from_str(s: &str) -> Result<Self, Self::Err> {
        match s {
            "AlgoExpert" => Ok(Site::AlgoExpert),
            "LeetCode" => Ok(Site::LeetCode),
            _ => Err(()),
        }
    }
}

#[derive(Debug, PartialEq, Eq, Clone)]
struct Problem {
    name: String,
    difficulty: Difficulty,
    language: Language,
    file_path: PathBuf,
    site: Site,
}

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord, Copy, Clone)]
struct Key<'a> {
    difficulty: &'a Difficulty,
    name: &'a String,
    site: &'a Site,
}

impl<'a> From<&'a Problem> for Key<'a> {
    fn from(problem: &'a Problem) -> Self {
        Self {
            difficulty: &problem.difficulty,
            name: &problem.name,
            site: &problem.site,
        }
    }
}

/// Returns paths to all files discovered within given path folder.
fn walkdir<P: Into<PathBuf>>(root: P) -> io::Result<HashSet<PathBuf>> {
    let root: PathBuf = root.into();
    let mut paths: HashSet<PathBuf> = HashSet::new();
    let mut dirs: Vec<PathBuf> = Vec::new();

    if root.is_dir() {
        dirs.push(root);
    } else if root.is_file() {
        paths.insert(root);
    }

    while let Some(curr_dir) = dirs.pop() {
        for dir_entry in fs::read_dir(curr_dir)? {
            let dir_entry = dir_entry?;
            let file_type = dir_entry.file_type()?;
            if file_type.is_file() {
                paths.insert(dir_entry.path());
            } else if file_type.is_dir() {
                dirs.push(dir_entry.path());
            }
        }
    }

    Ok(paths)
}

/// Capitalize the first letter of a string.
fn capitalize_first(s: &str) -> String {
    let mut char_iter = s.chars();
    match char_iter.next() {
        Some(first_char) => first_char.to_uppercase().chain(char_iter).collect(),
        None => String::new(),
    }
}

/// Correctly format the name of a problem.
fn format_problem_name(file_name: &str) -> String {
    let file_name = file_name.trim();
    let name_parts = file_name.split('_');

    name_parts
        .into_iter()
        .map(str::trim)
        .map(capitalize_first)
        .collect::<Vec<String>>()
        .join(" ")
}

/// Returns the difficulty of a problem given its path.
/// This reads the file and looks for a specifically formatted line.
fn parse_difficulty_from_path<P: AsRef<Path>>(path: P) -> Option<Difficulty> {
    let file = File::open(path).unwrap();
    let reader = BufReader::new(file);

    for line in reader.lines() {
        if let Ok(difficulty) = Difficulty::from_str(&line.ok()?) {
            return Some(difficulty);
        }
    }
    None
}

/// Given the path of a problem file, return a `Problem`.
fn parse_problem_from_path<P: AsRef<Path>>(path: P) -> Option<Problem> {
    let path = path.as_ref();
    let file_name = path.file_stem()?.to_str()?;
    let extension = path.extension()?.to_str()?;
    let name = format_problem_name(file_name);
    let difficulty = parse_difficulty_from_path(path)?;
    let language = Language::from_extension(extension)?;
    let site = path
        .components()
        .map(|comp| comp.as_os_str().to_str().unwrap())
        .find_map(|s| Site::from_str(s).ok())?;

    Some(Problem {
        name,
        difficulty,
        language,
        file_path: path.to_owned(),
        site,
    })
}

/// Group list of 1NF problems by their key. In other words, Each entry becomes a unique problem.
fn group_problems_by_key(problems: &[Problem]) -> BTreeMap<Key, HashMap<Language, &Path>> {
    let mut grouped: BTreeMap<Key, HashMap<Language, &Path>> = BTreeMap::new();

    for problem in problems {
        let key: Key = problem.into();
        grouped
            .entry(key)
            .or_default()
            .insert(problem.language, problem.file_path.as_path());
    }

    grouped
}

/// Returns set of all languages solved in list of problems.
fn find_solved_languages(problems: &[Problem]) -> BTreeSet<Language> {
    problems.iter().map(|prob| prob.language).collect()
}

/// Returns mapping of difficulty to the number of problems solved with that difficulty.
fn count_difficulties_solved(
    table: &BTreeMap<Key, HashMap<Language, &Path>>,
) -> HashMap<Difficulty, usize> {
    let mut counts = HashMap::new();
    for key in table.keys() {
        *counts.entry(*key.difficulty).or_default() += 1;
    }
    counts
}

fn count_languages_solved(problems: &[Problem]) -> BTreeMap<Language, usize> {
    let mut counts = BTreeMap::new();
    for problem in problems {
        *counts.entry(problem.language).or_default() += 1;
    }
    counts
}

/// Returns a path formatted as a markdown link.
fn format_md_link<P: AsRef<Path>>(path: P) -> String {
    let path = path.as_ref();
    let file_name = path.file_name().unwrap().to_str().unwrap();
    let str_path = path.to_str().unwrap().replace('\\', "/");
    format!("[{file_name}]({str_path})")
}

/// Convert a header and rows of a table to a markdown table.
fn header_rows_to_string(header: &[String], rows: &[Vec<String>]) -> String {
    let columns = header.len();
    let mut out = String::new();

    // Format header
    out.push_str("| ");
    out.push_str(&header.join(" | "));
    out.push_str(" |\n");
    let sep = "---";
    out.push('|');
    for _ in 0..columns {
        out.push_str(&format!(" {sep} |"));
    }
    out.push('\n');

    for row in rows {
        assert_eq!(columns, row.len());
        out.push_str("| ");
        out.push_str(&row.join(" | "));
        out.push_str(" |\n");
    }

    out
}

/// ### Unique Problems Solved by Difficulty
/// * Easy: ww
/// * Medium: xx
/// * Hard: yy
/// * Very Hard: zz
/// total: summed
///
/// ### Problems Solved by Language
/// * Rust: n
/// * C++: m
/// * ......
///
fn md_stats(problems: &[Problem]) -> String {
    use Difficulty::*;

    let unique_problems = group_problems_by_key(problems);
    let difficulty_counts = count_difficulties_solved(&unique_problems);
    let total_uniques = difficulty_counts.values().sum();
    assert_eq!(unique_problems.len(), total_uniques);

    let languages_solved = count_languages_solved(problems);
    let total_solved: usize = languages_solved.values().sum();
    assert_eq!(problems.len(), total_solved);

    let mut out = String::from("### Unique Problems Solved By Difficulty\n");
    for difficulty in [Easy, Medium, Hard, VeryHard] {
        let count = difficulty_counts.get(&difficulty).copied().unwrap_or(0);
        out.push_str(&format!("* {difficulty}: {count}\n"));
    }
    out.push_str(&format!("\nTotal: {total_uniques}\n\n"));

    out.push_str("### Problems Solved By Language\n");
    for (language, count) in languages_solved {
        out.push_str(&format!("* {language}: {count}\n"));
    }
    out.push_str(&format!("\nTotal: {total_solved}\n\n"));

    out
}

fn md_table(problems: &[Problem]) -> String {
    let unique_problems = group_problems_by_key(problems);
    let languages_in_table = find_solved_languages(problems);

    let header: Vec<String> = ["Problem Name", "Difficulty"]
        .into_iter()
        .map(|s| s.to_owned())
        .chain(languages_in_table.iter().map(Language::to_string))
        .collect();

    let mut rows: Vec<Vec<String>> = Vec::new();

    for (key, language_paths) in &unique_problems {
        let mut curr_row: Vec<String> = vec![key.name.clone(), key.difficulty.to_string()];

        for lang in &languages_in_table {
            curr_row.push(match language_paths.get(lang) {
                Some(path) => format_md_link(path),
                None => String::new(),
            });
        }
        rows.push(curr_row);
    }

    header_rows_to_string(&header, &rows)
}

fn main() {
    let readme_base_file = "README_base.md";
    let readme_file = "README.md";
    let site_dirs = ["./AlgoExpert", "./LeetCode"];

    // Contains paths for all solution files for all languages.
    let solution_paths: HashSet<PathBuf> = site_dirs
        .into_iter()
        .flat_map(|dir| walkdir(dir).unwrap())
        .collect();
    let num_solution_paths = solution_paths.len();

    // 1NF list of all problems.
    let problems: Vec<Problem> = solution_paths
        .into_iter()
        .flat_map(parse_problem_from_path)
        .collect();

    assert_eq!(num_solution_paths, problems.len());
    for problem in &problems {
        println!("{problem:?}");
    }

    // ------------------------------------------------------
    let mut readme_sections: Vec<String> = vec![
        // Base prewritten Readme.
        fs::read_to_string(readme_base_file).unwrap(),
        // General Readme.
        "## General Info".into(),
        md_stats(&problems),
    ];

    // Each website gets a section.
    for site in [Site::AlgoExpert, Site::LeetCode] {
        let site_problems: Vec<Problem> = problems
            .iter()
            .filter(|prob| prob.site == site)
            .cloned()
            .collect();

        readme_sections.push(format!("## {site}"));
        readme_sections.push(md_stats(&site_problems));
        readme_sections.push(md_table(&site_problems));
    }

    let generated_readme = readme_sections.join("\n");
    fs::write(readme_file, generated_readme).unwrap();
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn parse_difficulty() {
        use Difficulty::*;
        let str_to_result = [
            ("Difficulty: Easy", Ok(Easy)),
            ("Difficulty: Medium", Ok(Medium)),
            ("Difficulty: Hard", Ok(Hard)),
            ("Difficulty: Very Hard", Ok(VeryHard)),
            ("Difficulty: Rando", Err(())),
            ("sure to fail.", Err(())),
        ];
        for (input_str, expected) in str_to_result {
            let result = Difficulty::from_str(input_str);
            assert_eq!(result, expected);
        }
    }

    #[test]
    fn parsing_problem_name() {
        let expectations = [
            ("testing", "Testing"),
            ("parse_binary_tree", "Parse Binary Tree"),
        ];
        for (input_str, expected) in expectations {
            assert_eq!(format_problem_name(input_str), expected);
        }
    }
}
