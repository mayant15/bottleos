use crate::kprintln;
use alloc::{boxed::Box, rc::Rc, vec, vec::Vec};
use lazy_static::lazy_static;
use spin::Mutex;
use x86_64::instructions::hlt;

type ProcessQueue = alloc::collections::VecDeque<ProcessBlock>;

lazy_static! {
    /// A singleton instance of the Scheduler class to control processes
    static ref SCHEDULER: Mutex<Scheduler> = Mutex::new(Scheduler {
        jobs: ProcessQueue::new(),
        ready_jobs: ProcessQueue::new(),
        next_pid: 0,
    });
}

pub fn start() -> ! {
    create_kernel_processes();
    SCHEDULER.lock().start();
}

#[derive(Debug, PartialEq, Eq)]
pub enum ProcessState {
    New,
    Ready,
    Running,
    Blocked,
    End,
}

#[derive(Debug)]
struct ProcessBlock {
    pid: usize,
    state: ProcessState,
    task: fn(),
}

impl ProcessBlock {
    fn run(&self) {
        (self.task)();
    }
}

/// An interface to manipulate processes. The ProcessBlock is the actual internal representation.
#[derive(Debug)]
pub struct Process {
    pid: usize,
}

impl Process {
    // TODO: This should be atomic, don't pre-empt a thread that's creating a child process.
    pub fn new(task: fn()) -> Self {
        // Create a process block
        let pid = SCHEDULER.lock().get_next_pid();
        let block = ProcessBlock {
            pid,
            task,
            state: ProcessState::New,
        };

        // NOTE: Disable interrupts here?
        SCHEDULER.lock().register_process(block);

        // Return an interface to this process block
        Process { pid: pid }
    }

    pub fn is_valid(&self) -> bool {
        true
    }
}

fn process_1_body() {
    kprintln!("This is process 1!");

    let heap_value = Box::new(41);
    kprintln!("heap_value at {:p}", heap_value);

    let mut vec = Vec::new();
    for i in 0..500 {
        vec.push(i);
    }
    kprintln!("vec at {:p}", vec.as_slice());
}

fn process_2_body() {
    kprintln!("This is process 2!");

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
}

fn create_kernel_processes() {
    // TODO: IPC. Should these closures be allowed to capture their surroundings? Should they run
    // immediately? Should I have a init -> set_data -> start -> join API?
    let _proc1 = Process::new(process_1_body);
    let _proc2 = Process::new(process_2_body);
}

#[derive(Debug)]
struct Scheduler {
    // TODO: No Mutexes here, everything is running on a single core. Make this thread-safe
    jobs: ProcessQueue,
    ready_jobs: ProcessQueue,

    next_pid: usize,
}

impl Scheduler {
    fn start(&mut self) -> ! {
        kprintln!(">> Starting scheduler...");
        loop {
            if self.jobs.len() == 0 {
                // I don't have any more jobs left, just halt
                hlt();
            } else {
                self.step();
            }
        }
    }

    /// The Scheduler simply moves jobs from job queue to ready, then
    /// executes them one by one
    fn step(&mut self) {
        if self.jobs.len() != 0 && self.ready_jobs.len() == 0 {
            let mut job = self.jobs.pop_front().unwrap();
            job.state = ProcessState::Ready;
            self.ready_jobs.push_back(job);
        }

        if self.ready_jobs.len() != 0 {
            let mut job = self.ready_jobs.pop_front().unwrap();
            job.state = ProcessState::Running;
            job.run();
            job.state = ProcessState::End;
        }
    }

    fn get_next_pid(&self) -> usize {
        self.next_pid
    }

    fn register_process(&mut self, block: ProcessBlock) {
        self.jobs.push_back(block);
        self.next_pid += 1;
    }
}

// TODO: Unit tests for this
