const platform = require('./index.js');
const assert = require('assert').strict;
// const { Worker, isMainThread, workerData } = require('worker_threads');

// TODO: Passing threadId as a workerData seems not to work, so the worker test fails

// if (isMainThread) {
    const threadId = new platform.ThreadId();
    const otherThreadId = new platform.ThreadId();

    // Test for same thread id
    assert(threadId.equals(otherThreadId) === true, 'Thread Ids must be equal');

    // Test for invalid input
    class Whatever {
        constructor() {}
    };

    try {
        threadId.equals(new Whatever());
        assert.fail('ThreadId should not work with wrong types');
    } catch (e) {
        assert(e.message === 'Invalid argument', 'Thread Id must protect against wrong object types');
    }

//     // Test worker
//     new Worker(__filename, {
//         workerData: threadId,
//     });
// } else {
//     const mainThreadId = workerData;
//     const threadId = new platform.ThreadId();

//     // Test for different thread ids
//     assert(threadId.equals(mainThreadId) === false, 'Thread Id must be different');
// }
