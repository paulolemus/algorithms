//! Generate README tables of all solutions.

use std::collections::{BTreeMap, BTreeSet, HashMap, HashSet};
use std::fmt::{self, Display};
use std::fs::{self, File};
use std::io::{self, BufRead, BufReader};
use std::path::{Path, PathBuf};
use std::str::FromStr;

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

#[derive(Debug, PartialEq, Eq)]
struct Problem {
    name: String,
    difficulty: Difficulty,
    language: Language,
    file_path: PathBuf,
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
fn parse_problem_name(file_name: &str) -> String {
    let file_name = file_name.trim();
    let name_parts = file_name.split('_');

    name_parts
        .into_iter()
        .map(|s| s.trim())
        .map(|s| capitalize_first(s))
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
    let file_name = path.file_stem().unwrap().to_str().unwrap();
    let extension = path.extension().unwrap().to_str().unwrap();
    let name = parse_problem_name(file_name);
    let difficulty = parse_difficulty_from_path(path)?;
    let language = Language::from_extension(extension)?;

    Some(Problem {
        name,
        difficulty,
        language,
        file_path: path.to_owned(),
    })
}

#[derive(Debug, PartialEq, Eq, PartialOrd, Ord)]
struct Key {
    difficulty: Difficulty,
    name: String,
}

/// Returns a path formatted as a markdown link.
fn md_link_format<P: AsRef<Path>>(path: P) -> String {
    let path = path.as_ref();
    let file_name = path.file_name().unwrap().to_str().unwrap();
    let str_path = path.to_str().unwrap();
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
    out.push_str("|");
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

fn main() {
    // Each website root folder.
    let site_dirs = ["./AlgoExpert"];
    let readme_base_file = "README_base.md";
    let readme_file = "README.md";

    // Contains paths for all solution files for all languages.
    let solution_paths: HashSet<PathBuf> = site_dirs
        .into_iter()
        .map(|dir| walkdir(dir).unwrap())
        .flatten()
        .collect();

    let problems: Vec<Problem> = solution_paths
        .into_iter()
        .map(parse_problem_from_path)
        .map(|opt| opt.unwrap())
        .collect();

    for problem in &problems {
        println!("{problem:?}");
    }

    // Languages used in this block.
    // BTreeSet for sorted language iteration, vs HashSet -> Vec -> vec.sort.
    let languages: BTreeSet<Language> = problems.iter().map(|problem| problem.language).collect();
    let mut table: BTreeMap<Key, HashMap<Language, PathBuf>> = BTreeMap::new();

    for problem in problems {
        let problem_key = Key {
            difficulty: problem.difficulty,
            name: problem.name,
        };
        table
            .entry(problem_key)
            .or_default()
            .insert(problem.language, problem.file_path);
    }

    // Table now holds all data as correctly formatted rows.
    // Generate a Markdown table.
    let header: Vec<String> = ["Problem Name", "Difficulty"]
        .into_iter()
        .map(|s| s.to_owned())
        .chain(languages.iter().map(|lang| lang.to_string()))
        .collect();

    let mut rows: Vec<Vec<String>> = Vec::new();

    for (key, language_paths) in table {
        let mut curr_row: Vec<String> = Vec::new();
        curr_row.push(key.name);
        curr_row.push(key.difficulty.to_string());

        for lang in &languages {
            curr_row.push(match language_paths.get(lang) {
                Some(path) => md_link_format(path),
                None => String::new(),
            });
        }
        rows.push(curr_row);
    }

    let markdown_table = header_rows_to_string(&header, &rows);
    println!("Markdown Table:\n{markdown_table}");

    // Generate output README.md file.
    let readme_base = fs::read_to_string(readme_base_file).unwrap();
    let subsection_header = "## Solved Problems\n\n";
    let readme = format!("{readme_base}\n{subsection_header}{markdown_table}");

    fs::write(readme_file, readme).unwrap();
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
            assert_eq!(parse_problem_name(input_str), expected);
        }
    }
}
