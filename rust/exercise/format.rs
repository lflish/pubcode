/*
    println!宏使用
*/

fn main()
{
    println!("10={:b}", 10);
    println!("10={:o}", 10);
    println!("10={}", 10);
    println!("10={:x}", 10);

    println!("------");

    println!("{}", "Hello World");

    /* debug 打印并不懂 */
    println!("{:?}", "Hello World");
}