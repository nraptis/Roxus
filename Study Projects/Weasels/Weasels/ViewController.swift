//
//  ViewController.swift
//  Weasels
//
//  Created by Raptis, Nicholas on 5/24/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        var temp = [Int](repeating: 0, count: 200)
        
        var arr1 = [5, 2, 3, 17, 12, 6, 11, 5, 2, 1, 35, 1, 16, 43, 5, 8, 22, 75, 34, 54, 41, 73]
        var arr2 = [6, 8, 5, 99, 3, 35, 1, 5, 2, 4, 17, 12, 14, 27, 33, 1, 6]
        var arr3 = [5, 5, 5, 2, 3, 7, 35, 1, 17, 12, 6, 9]
        var arr4 = [17, 12, 6, 5, 2, 3, 9, 6, 24, 64, 4, 1, 6, 31, 6, 8, 24]
        var arr5 = [6, 5, 4, 3, 2, 1, 0, 7, 2, 11]
        var arr6 = [99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 54, 55, 56, 57, 58, 59, 1, 0, -1, -2, 2, 13, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
        
        print("Arr1 = \(arr1)")
        print("Arr2 = \(arr2)")
        print("Arr3 = \(arr3)")
        print("Arr4 = \(arr4)")
        print("Arr5 = \(arr5)")
        print("Arr6 = \(arr6)")
        
        //insertionSort(&arr1)
        //insertionSort(&arr2)
        //insertionSort(&arr3)
        //insertionSort(&arr4)
        //insertionSort(&arr5)
        //insertionSort(&arr6)
        
        superSort(&arr1, &temp)
        superSort(&arr2, &temp)
        superSort(&arr3, &temp)
        superSort(&arr4, &temp)
        superSort(&arr5, &temp)
        superSort(&arr6, &temp)
        
        
        //quickSort(arr: &arr1, start: 0, end: arr1.count - 1)
        //quickSort(arr: &arr2, start: 0, end: arr2.count - 1)
        //quickSort(arr: &arr3, start: 0, end: arr3.count - 1)
        //quickSort(arr: &arr4, start: 0, end: arr4.count - 1)
        //quickSort(arr: &arr5, start: 0, end: arr5.count - 1)
        //quickSort(arr: &arr6, start: 0, end: arr6.count - 1)
        
        /*
        mergeSort(&arr1, 0, arr1.count - 1)
        mergeSort(&arr2, 0, arr2.count - 1)
        mergeSort(&arr3, 0, arr3.count - 1)
        mergeSort(&arr4, 0, arr4.count - 1)
        mergeSort(&arr5, 0, arr5.count - 1)
        mergeSort(&arr6, 0, arr6.count - 1)
        */
        
        print("S-Arr1 = \(arr1)")
        print("Ind0 = \(binarySearch(&arr1, 0))")
        
        print("S-Arr2 = \(arr2)")
        print("Ind1 = \(binarySearch(&arr2, 1))")
        
        print("S-Arr3 = \(arr3)")
        print("Ind2 = \(binarySearch(&arr3, 2))")
        
        print("S-Arr4 = \(arr4)")
        print("Ind3 = \(binarySearch(&arr4, 3))")
        
        print("S-Arr5 = \(arr5)")
        print("Ind4 = \(binarySearch(&arr5, 4))")
        
        print("S-Arr6 = \(arr6)")
        print("Ind5 = \(binarySearch(&arr6, 5))")
        
    }
    
    func binarySearch(_ arr: inout [Int], _ value: Int) -> Int? {
        
        var startIndex = 0
        var endIndex = arr.count - 1
        while startIndex < endIndex {
            
            var mid = (startIndex + endIndex) / 2
            
            if arr[mid] == value { return mid }
            
            if arr[mid] < value {
                startIndex = mid + 1
            } else {
                endIndex = mid
            }
        }
        return nil
    }
    
    func superSort(_ arr: inout [Int], _ temp: inout [Int]) {
        
        //7 is the magic number
        let blockSize = 7
        var startIndex = 0
        
        //Perform insertion sort on the many small blocks.
        while startIndex < arr.count {
            var endIndex = startIndex + blockSize
            if endIndex > arr.count { endIndex = arr.count }
            for i in 0..<endIndex {
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
                //Cope the temp array back on each iteration...
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
    
    func insertionSort(_ arr: inout [Int]) {
        
        for i in 1..<arr.count {
            
            var x = arr[i]
            var j = i - 1
            while j >= 0, arr[j] > x {
                arr[j + 1] = arr[j]
                j -= 1
            }
            arr[j + 1] = x
        }
        
        
        
    }
    
    func insertionSortBad(arr: inout [Int]) {
        var index = 1
        while index < arr.count {
            var j = index - 1
            while j >= 0, arr[j] > arr[j + 1] {
                arr.swapAt(j, j + 1)
                j -= 1
            }
            index += 1
        }
    }
    
    func mergeSort(_ arr: inout [Int], _ start: Int, _ end: Int) -> Void {
        
        if (end - start) < 1 { return }
        let split = (start + end) / 2
        
        if split > start { mergeSort(&arr, start, split) }
        if (split + 1) < end { mergeSort(&arr, split + 1, end) }
        
        var temp = [Int](repeating: 0, count: arr.count)
        var index: Int = start
        var i = start
        var j = split + 1
        
        while i <= split && j <= end {
            if arr[i] < arr[j] {
                temp[index] = arr[i]
                i += 1
            } else {
                temp[index] = arr[j]
                j += 1
            }
            index += 1
        }
        
        while i <= split {
            temp[index] = arr[i]
            i += 1
            index += 1
        }
        
        while j <= end {
            temp[index] = arr[j]
            j += 1
            index += 1
        }
        
        for k in start..<(end + 1) { arr[k] = temp[k] }
    }
    
    func quickSort(arr: inout [Int], start: Int, end: Int) {
        if end <= start { return }
        let part = partition(arr: &arr, start: start, end: end)
        if (part - 1) > start { quickSort(arr: &arr, start: start, end: part - 1)}
        if (part + 1) < end { quickSort(arr: &arr, start: part + 1, end: end)}
        
    }
    
    func partition(arr: inout [Int], start: Int, end: Int) -> Int {
        let value =  arr[(start + end) / 2]
        var a = start; var b = end
        while a < b {
            while (arr[a] < value) && (a < b) { a += 1 }
            while (arr[b] > value) && (b > a) { b -= 1 }
            if a < b {
                arr.swapAt(a, b)
                a += 1
                b -= 1
            }
        }
        return a
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }


}

