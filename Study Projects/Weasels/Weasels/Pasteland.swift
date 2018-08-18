func superSort(_ arr: inout [Int], _ temp: inout [Int]) {
    
    //7 is the magic number
    let blockSize = 7
    var startIndex = 0
    
    //Perform insertion sort on the many small blocks.
    while startIndex < arr.count {
        var endIndex = startIndex + blockSize
        if endIndex > arr.count { endIndex = arr.count }
        for i in startIndex..<endIndex {
            let hold = arr[i]
            var j = i - 1
            while j >= startIndex && arr[j] > hold {
                arr[j + 1] = arr[j]
                j -= 1
            }
            arr[j + 1] = hold
        }
        startIndex += 7
    }
    
    //Perform a modified bottom-up merge-sort, given that
    //all blocks of our magic size are already sorted...
    var sortBlockSize = blockSize
    while sortBlockSize < arr.count {
        var start = 0
        while start < arr.count {
            //We merge a 2 groups which are both the block size (and both soerted)
            let split = start + sortBlockSize
            var end = split + sortBlockSize
            if end >= arr.count { end = arr.count }
            guard split < arr.count else { break }
            var a = start; var b = split; var ind = start
            while a < split && b < end {
                if arr[a] < arr[b] {
                    temp[ind] = arr[a];a += 1;ind += 1
                } else {
                    temp[ind] = arr[b];b += 1;ind += 1
                }
            }
            
            while a < split {
                temp[ind] = arr[a];a += 1;ind += 1
            }
            while b < end {
                temp[ind] = arr[b];b += 1;ind += 1
            }
            
            //Copy the temp array back on each iteration...
            for k in start..<end {
                arr[k] = temp[k]
            }
            //Go to the end of our "double-block" to start the next merge...
            start = end
        }
        //Double the size of the merge blocks every time.
        //Essentially, this is the log(n) in n * log(n)
        sortBlockSize *= 2
    }
}
