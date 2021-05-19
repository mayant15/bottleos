# Tests

[Reference](https://os.phil-opp.com/testing/)

We need to use a custom test handler for implementing tests for `no_std` applications.

```rust
#![feature(custom_test_frameworks)]
#![test_runner(bottleos::test_runner)]
#![reexport_test_harness_main = "test_main"]
```

The `test_runner` function in `lib.rs` executes all tests in a for-loop. The `Testable` trait implements a uniform
output format.

The `custom_test_frameworks` feature generates a main function for us, which we need to call from the `_start`
entrypoint. This `_start` function can be called manually or be wrapped with the `entry_point!` macro from the
bootloader crate.

