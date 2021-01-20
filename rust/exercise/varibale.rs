/* 
    rust基本变量 
    date: 2020-01-20
*/

fn test_int()
{
    let test1:u8 = 10;

    let test2:u16 = 1000;

    let test3 = 1000; /* i32 */

    let test4 = 1000000_u64; /* i32 */

    let test5 = 0x10_ff_ff_u128; /* i32 */

    println!("{}", test1);
    println!("{}", test2);
    println!("{}", test3);
    println!("{}", test4);
    println!("{:x}", test5);

}

fn int_and_int64()
{
    let t1 = 100;
    let t2: i64 = t1;

    let var1 : i32 = 64;

    /* 这里会失败，但是 t1 那个例子会成功 */
    //let var2 : i64 = var1;

    let var3 : i64 = var1 as i64;

    println!("{}", t2);
    println!("{}", var3);
}

/* 第二部分后 整理
fn test_ptr()
{
    let test1 : i32 = 2020;

    //let Box<i32> = &test1;
}
*/

fn main()
{
    test_int();

    int_and_int64();
}