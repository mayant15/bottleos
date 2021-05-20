use crate::kprintln;
use x86_64::instructions::hlt;
use alloc::{boxed::Box, rc::Rc, vec, vec::Vec, collections::VecDeque};
use lazy_static::lazy_static;

type ProcessQueue = alloc::collections::VecDeque<Box<Process>>;

lazy_static! {
    /// A singleton instance of the Scheduler class to control processes
    static ref SCHEDULER: Scheduler = Scheduler { 
        jobs: ProcessQueue::new(),
        ready_jobs: ProcessQueue::new(),
    };
}

pub fn start() -> ! {
    create_kernel_processes();
    SCHEDULER.start();
}

pub enum ProcessState {
    Start,
    Running,
    Waiting,
    Ready,
    End,
}

pub struct Process {
    pid: u32,
    state: ProcessState,
}

impl Process {
    pub fn new(task: impl Fn()) -> Self {
        // Add task to queue
        Process {
            pid: 0,
            state: ProcessState::Ready,
        }
    }
}

fn create_kernel_processes() {
    // TODO: IPC. Should these closures be allowed to capture their surroundings? Should they run
    // immediately? Should I have a init -> set_data -> start -> join API?
    let proc1 = Process::new(|| {
        let heap_value = Box::new(41);
        kprintln!("heap_value at {:p}", heap_value);

        let mut vec = Vec::new();
        for i in 0..500 {
            vec.push(i);
        }
        kprintln!("vec at {:p}", vec.as_slice());
    });

    let proc2 = Process::new(|| {
        let reference_counted = Rc::new(vec![1, 2, 3]);
        let cloned_reference = reference_counted.clone();
        kprintln!(
            "current reference count is {}",
            Rc::strong_count(&cloned_reference)
        );
        core::mem::drop(reference_counted);
        kprintln!(
            "reference count is {} now",
            Rc::strong_count(&cloned_reference)
        );
    });
}

struct Scheduler {
    jobs: ProcessQueue,
    ready_jobs: ProcessQueue,
}

impl Scheduler {
    fn start(&self) -> ! {
        loop {
            self.step();
        }
    }

    fn step(&self) {
        hlt();
    }
}

