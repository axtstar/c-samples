use pgx::*;

pg_module_magic!();

#[pg_extern]
fn hello_test2() -> &'static str {
    "Hello, test2"
}

#[cfg(any(test, feature = "pg_test"))]
mod tests {
    use pgx::*;

    #[pg_test]
    fn test_hello_test2() {
        assert_eq!("Hello, test2", crate::hello_test2());
    }

}

#[cfg(test)]
pub mod pg_test {
    pub fn setup(_options: Vec<&str>) {
        // perform one-off initialization when the pg_test framework starts
    }

    pub fn postgresql_conf_options() -> Vec<&'static str> {
        // return any postgresql.conf settings that are required for your tests
        vec![]
    }
}
