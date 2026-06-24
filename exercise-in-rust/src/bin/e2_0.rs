use std::io::{self, Write};

fn main() {
    print!("Please enter your first name: ");
    io::stdout().flush().unwrap();

    let input = "Yang";
    let name = input.split_whitespace().next().unwrap();

    let greeting = format!("Hello, {}!", name);

    let pad: usize = 1;
    let rows: usize = pad * 2 + 3;
    let cols: usize = greeting.len() + pad * 2 + 2;

    println!();

    for r in 0..rows {
        let mut c = 0;

        while c < cols {
            if r == pad + 1 && c == pad + 1 {
                print!("{}", greeting);
                c += greeting.len();
            } else {
                if r == 0 || r == rows - 1 || c == 0 || c == cols - 1 {
                    print!("*");
                } else {
                    print!(" ");
                }
                c += 1;
            }
        }
        println!();
    }
}