//
//  ViewController.swift
//  Mueller
//
//  Created by Raptis, Nicholas on 6/2/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        //namesScores("p022_names.txt")

        //quadraticPrimes()
        //numberSpiralDiagonals()
        //distinctPowers()
        //digitFifthPowers()
        //permutePounds()

        pandigitalProducts()


        //digitCancelingFractions()

    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    func namesScores(_ fileName: String) {
        
        var path = Bundle.main.bundlePath + "/" + fileName
        
        var fileURL = URL(fileURLWithPath: path)
        
        do {
            var fileText = try String(contentsOf: fileURL)
            
            var nameDirtyList = fileText.components(separatedBy: ",")
            var nameList = [String]()
            
            for name in nameDirtyList {
                var cleanName = String(name)
                cleanName = cleanName.replacingOccurrences(of: ",", with: "")
                cleanName = cleanName.replacingOccurrences(of: "\"", with: "")
                cleanName = cleanName.trimmingCharacters(in: .whitespacesAndNewlines)

                if cleanName.count > 0 {
                    nameList.append(cleanName)
                }
            }
            
            nameList.sort(by: { (a, b) -> Bool in
                a < b
            })
            
            //var nameScores = [Int](repeating: 0, count: nameList.count)
            
            var index: Int = 1
            let scoreList = nameList.map { (str: String) -> Int in
                
                let string = str.lowercased()
                
                let uni = Array(string.unicodeScalars)
                
                var ciSum = 0
                let a = Int(UnicodeScalar("a")!.value)
                for i: Int in 0..<uni.count {
                    var charIndex = (Int(uni[i].value) - a) + 1
                    ciSum += charIndex
                }
                
                var res = ciSum * index
                index += 1
                return res
            }
            
            for i: Int in 0..<nameList.count {
                //print("Name [\(nameList[i])] Score = \(scoreList[i])")
            }
            
            var addrLength: Int = 64
            
            var adderLines = [[Int]]()
            
            for i: Int in 0..<scoreList.count {

                let digits = String(scoreList[i]).flatMap { Int(String($0)) }
                var row = [Int](repeating:0, count: addrLength)
                var rowIndex = row.count - 1
                var digiIndex = digits.count - 1
                while digiIndex >= 0 && rowIndex >= 0 {
                    row[rowIndex] = digits[digiIndex]
                    rowIndex -= 1
                    digiIndex -= 1
                }
                adderLines.append(row)
            }
            
            var carry = [Int](repeating:0, count: addrLength)
            var result = [Int](repeating:0, count: addrLength)
            
            var rowIndex = addrLength - 1
            while rowIndex >= 0 {
                var sum = carry[rowIndex]
                for line in adderLines {
                    sum += line[rowIndex]
                }
                
                if sum > 10 {
                    var c = sum / 10
                    sum = sum % 10
                    if rowIndex > 0 {
                        carry[rowIndex - 1] = c
                    }
                }
                result[rowIndex] = sum
                rowIndex -= 1
            }
            print("namesScores Result: \(result)")
        } catch {
            
        }
    }
    
    func quadraticPrimes() {
        var maxPrimeCount: Int = 0
        
        var bestA: Int = 0
        var bestB: Int = 0
        
        for a: Int in -1000..<1001 {
            for b: Int in -1000..<1001 {

                var prime: Bool = true
                var primeCount: Int = 0
                
                var n: Int = 0

                while prime {
                    let value: Int = n * n + a * n + b
                    if isPrime(value) {
                        prime = true
                        primeCount += 1
                    } else {
                        prime = false
                    }
                    n += 1
                }
                
                if primeCount > maxPrimeCount {
                    bestA = a
                    bestB = b
                    maxPrimeCount = primeCount
                }
            }
        }
        
        print("quadraticPrimes Result = \(bestA * bestB)")
        
    }
    
    func numberSpiralDiagonals() {
        
        var spiralGridSize: Int = 1001
        
        var spiral = [[Int]](repeating: [Int](repeating: 0, count: spiralGridSize), count: spiralGridSize)
        
        let cx: Int = spiralGridSize / 2
        let cy: Int = cx
        
        var value: Int = 1
        
        var ring: Int = 1
        let maxRing: Int = spiralGridSize / 2
        
        var cursorX: Int = cx
        var cursorY: Int = cy
        
        spiral[cursorX][cursorY] = value
        value += 1
        
        while ring <= maxRing {
            cursorX += 1
            
            spiral[cursorX][cursorY] = value
            value += 1
            
            let bottomY = cy + ring
            while cursorY < bottomY {
                
                cursorY += 1
                spiral[cursorX][cursorY] = value
                value += 1
                
            }
            
            //move left until we hit the wall../
            let leftX: Int = cx - ring
            while cursorX > leftX {
                cursorX -= 1
                
                spiral[cursorX][cursorY] = value
                value += 1
            }
            
            //move to the top wall.....
            let topX: Int = cy - ring
            while cursorY > topX {
                cursorY -= 1
                
                spiral[cursorX][cursorY] = value
                value += 1
            }
            
            //move back to the right.....
            var rightX:Int = cx + ring
            while cursorX < rightX {
                cursorX += 1
                
                spiral[cursorX][cursorY] = value
                value += 1
            }
            ring += 1
        }
        
        
        var diagX1: Int = 0
        var diagX2: Int = spiral.count - 1
        var diagY: Int = 0
        
        var dSum1: Int = 0
        var dSum2: Int = 0
        
        
        while diagX1 < spiral.count {
            
            dSum1 += spiral[diagX1][diagY]
            dSum2 += spiral[diagX2][diagY]
            
            diagY += 1
            diagX1 += 1
            diagX2 -= 1
        }
        
        //Note: We subtract 1 because we pass over it twice...
        print("Sum of diagonals: \(dSum1 + dSum2 - 1)")
        
    }
    
    func distinctPowers() {
        var maxCount: Int = 100
        var powersList = [[Int]]()
        for var a: Int in 2..<(maxCount + 1) {
            for var b: Int in 2..<(maxCount + 1) {

                var digitsA = String(a).flatMap { Int(String($0)) }
                var result = digitsA
                for _ in 1..<b {
                    result = longMultiply(int1: digitsA, int2: result)
                }
                
                var exists: Bool = false
                for index: Int in 0..<powersList.count {
                    
                    var chk = powersList[index]
                    if chk.count == result.count {
                        var equal: Bool = true
                        for i: Int in 0..<chk.count {
                            if chk[i] != result[i] {
                                equal = false
                                break
                            }
                        }
                        if equal == true {
                            exists = true
                            break
                        }
                    }
                }
                if exists == false {
                    powersList.append(result)
                }
            }
        }
        print("distinctPowers.count = \(powersList.count)")
    }

    func digitFifthPowers() {
        var maxNumber: Int = 999999
        var resultList = [Int]()
        for i: Int in 2..<maxNumber {
            var digits = String(i).flatMap { Int(String($0)) }
            var sumOfFifths: Int = 0
            for k: Int in 0..<digits.count {
                var digit: Int = digits[k]
                var fifth: Int = 1
                for powr in 0..<5 {
                    fifth *= digit
                }
                sumOfFifths += fifth
            }
            if sumOfFifths == i {
                print("Fifth Power Sum Num: \(sumOfFifths)")
                resultList.append(sumOfFifths)
            }
        }
        print("Final Result: \(resultList.reduce(0, +))")
    }

    func longMultiply(int1: [Int], int2: [Int]) -> [Int] {
        
        var longestNumberLength = int1.count
        if int2.count > longestNumberLength { longestNumberLength = int2.count }
        
        let resultMaxLength = (longestNumberLength + longestNumberLength + 1)
        var result = [Int](repeating: 0, count: resultMaxLength)
        
        var num1 = [Int](repeating: 0, count: resultMaxLength)
        var num2 = [Int](repeating: 0, count: resultMaxLength)
        
        var add = [[Int]](repeating: [Int](repeating: 0, count: resultMaxLength), count: resultMaxLength)
        var addCarry = [Int](repeating: 0, count: resultMaxLength)
        
        var index1 = int1.count - 1
        var index2 = int2.count - 1
        
        var resultIndex: Int = resultMaxLength - 1
        
        while resultIndex >= 0 {
            if index1 >= 0 { num1[resultIndex] = int1[index1] }
            if index2 >= 0 { num2[resultIndex] = int2[index2] }
            index1 -= 1
            index2 -= 1
            resultIndex -= 1
        }
        
        var leftMostDigit1: Int = resultMaxLength - 1
        var leftMostDigit2: Int = resultMaxLength - 1
        
        resultIndex = resultMaxLength - 1
        while resultIndex >= 0 {
            if num1[resultIndex] != 0 { leftMostDigit1 = resultIndex }
            if num2[resultIndex] != 0 { leftMostDigit2 = resultIndex }
            resultIndex -= 1
        }
        
        if leftMostDigit2 < leftMostDigit1 {
            for i: Int in 0..<resultMaxLength {
                let n1 = num1[i]
                num1[i] = num2[i]
                num2[i] = n1
            }
        }
        index2 = resultMaxLength - 1
        var addRow: Int = 0
        while index2 >= leftMostDigit2 {
            let shift = (resultMaxLength - 1) - index2
            for i: Int in 0..<resultMaxLength { addCarry[i] = 0 }
            index1 = resultMaxLength - 1
            while index1 >= 0 {
                var value = num1[index1] * num2[index2] + addCarry[index1]
                if value >= 10 {
                    let carry = value / 10
                    if index1 > 0 {
                        addCarry[index1 - 1] = carry
                    }
                    value = (value % 10)
                }
                if (index1 - shift) > 0 { add[addRow][index1 - shift] = value }
                index1 -= 1
            }
            addRow += 1
            index2 -= 1
        }
        
        for i: Int in 0..<resultMaxLength { addCarry[i] = 0 }
        var addCol: Int = resultMaxLength - 1
        while addCol >= 0 {
            var sum: Int = addCarry[addCol]
            addRow = 0
            while addRow < resultMaxLength {
                sum += add[addRow][addCol]
                addRow += 1
            }
            if sum >= 10 {
                let carry = sum / 10
                if addCol > 0 { addCarry[addCol - 1] = carry }
                sum = (sum % 10)
            }
            result[addCol] = sum
            addCol -= 1
        }
        
        //Now we trim the leading zeros...
        var leftMostDigit: Int = resultMaxLength - 1
        resultIndex = resultMaxLength - 1
        while resultIndex >= 0 {
            if result[resultIndex] != 0 { leftMostDigit = resultIndex }
            resultIndex -= 1
        }
        let finalLength: Int = resultMaxLength - leftMostDigit
        var trimmedResult = [Int](repeating: 0, count: finalLength)
        for i:Int in 0..<finalLength { trimmedResult[i] = result[i + leftMostDigit] }
        
        //print("\(int1) x \(int2) = \(trimmedResult)")
        
        return trimmedResult
    }

    func isPrime(_ number: Int) -> Bool {
        if number <= 2 { return false }
        let upperLimit = Int(sqrt(Double(number))) + 2
        for i in 2..<upperLimit {
            if (number % i) == 0 { return false }
        }
        return true
    }

    func permutePounds() {
        var coins = [1, 2, 5, 10, 20, 50, 100, 200]
        var coin_count_1  : Int = 0
        var permutations: Int = 0
        while coin_count_1 <= 200 {
            var coin_count_2  : Int = 0
            while coin_count_2 <= 100 {
                var coin_count_5  : Int = 0
                while coin_count_5 <= 40 {
                    var coin_count_10 : Int = 0
                    while coin_count_10 <= 20 {
                        var coin_count_20 : Int = 0
                        while coin_count_20 <= 10 {
                            var coin_count_50 : Int = 0
                            while coin_count_50 <= 4 {
                                var coin_count_100: Int = 0
                                while coin_count_100 <= 2 {
                                    var coin_count_200: Int = 0
                                    while coin_count_200 <= 1 {
                                        let sum = coins[0] * coin_count_1 +
                                            coins[1] * coin_count_2 +
                                            coins[2] * coin_count_5 +
                                            coins[3] * coin_count_10 +
                                            coins[4] * coin_count_20 +
                                            coins[5] * coin_count_50 +
                                            coins[6] * coin_count_100 +
                                            coins[7] * coin_count_200
                                        if sum == 200 {
                                            permutations += 1
                                        }
                                        coin_count_200 += 1
                                    }
                                    coin_count_100 += 1
                                }
                                coin_count_50 += 1
                            }
                            coin_count_20 += 1
                        }
                        coin_count_10 += 1
                    }
                    coin_count_5 += 1
                }
                coin_count_2 += 1
            }
            coin_count_1 += 1
        }
        print("Coin SUms: \(permutations)")
    }

    func isPandigital(num: Int) -> Bool {

        var result: Bool = true

        let digits = String(num).flatMap { Int(String($0)) }
        var digitExists = [Bool](repeating: false, count: 10)


        for digit in digits {
            if digit == 0 {
                result = false
            }
            if digitExists[digit] { result = false }
            digitExists[digit] = true
        }

        return result
    }

    func isTripletPandigital (num1: Int, num2: Int, num3: Int) -> Bool {
        var result: Bool = true

        let digits1 = String(num1).flatMap { Int(String($0)) }
        let digits2 = String(num2).flatMap { Int(String($0)) }
        let digits3 = String(num3).flatMap { Int(String($0)) }

        var digitExists = [Bool](repeating: false, count: 10)

        for digit in digits1 {
            if digitExists[digit] { result = false }
            digitExists[digit] = true
        }

        for digit in digits2 {
            if digitExists[digit] { result = false }
            digitExists[digit] = true
        }

        for digit in digits3 {
            if digit == 0 {
                result = false
            }
            if digitExists[digit] { result = false }
            digitExists[digit] = true
        }

        return result
    }

    private func permuteHelper(index: Int, arr: inout [Int], result: inout [[Int]]) {
        if index == (arr.count - 1) {
            result.append(arr)
        }
        var i: Int = index
        while i < arr.count {
            var hold = arr[i];arr[i] = arr[index];arr[index] = hold
            permuteHelper(index: index + 1, arr: &arr, result: &result)
            hold = arr[i];arr[i] = arr[index];arr[index] = hold
            i += 1
        }
    }

    func permute(arr: [Int]) -> [[Int]] {
        var result = [[Int]]()
        var arrCopy = [Int]()
        arrCopy.append(contentsOf: arr)
        permuteHelper(index: 0, arr: &arrCopy, result: &result)
        return result
    }

    func pandigitalProducts() {
        let numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9]
        let permuts = permute(arr: numbers)
        var total = 0
        var alreadyExistsTable = [Int:Bool]()
        for num in permuts {
            var numLen1: Int = 1
            var numLen2: Int = 1
            while numLen1 <= 4 {
                var num1: Int = 0
                for i in 0..<numLen1 {
                    num1 *= 10
                    num1 += num[i]
                }
                numLen2 = 1
                while numLen2 <= 4 {
                    var num2: Int = 0
                    for i in 0..<numLen2 {
                        num2 *= 10
                        num2 += num[i + numLen1]
                    }
                    let product = num1 * num2
                    let productString = String(product)
                    if productString.count + numLen1 + numLen2 == 9 {
                        var productDigits = productString.flatMap { Int(String($0)) }
                        let productStartIndex = numLen1 + numLen2
                        var equals: Bool = true
                        for k in 0..<productDigits.count {
                            if num[productStartIndex + k] != productDigits[k] {
                                equals = false
                            }
                        }
                        if equals {
                            if alreadyExistsTable[product] == nil {
                                alreadyExistsTable[product] = true
                                total += product
                            }
                        }
                    }
                    numLen2 += 1
                }
                numLen1 += 1
            }
        }
        print("Pandigital Result: \(total)")
    }

    func isEvenlyDivisible(num1: Int, num2: Int) -> Bool {
        if num1 <= 0 { return false }
        if num2 <= 0 { return false }
        let r: Int = num2 % num1
        return r == 0
    }

    func lcm(_ num1: Int, num2: Int) -> Int {
        let g = gcd(num1, num2: num2)
        if g != 0 {
            return (num1 * num2) / g
        }
        return 0
    }

    func gcd(_ num1: Int, num2: Int) -> Int {
        var smaller: Int = num1
        var larger: Int = num2
        if num2 < num1 {
            smaller = num2
            larger = num1
        }
        while smaller > 0 {
            let remainder = larger % smaller
            larger = smaller
            smaller = remainder
        }
        return larger
    }

    func digitCancelingFractions() {

        //2 digits in numerator
        //2 digits in demomenator

        var sumNumer = 0
        var sumDenom = 0

        for numer in 10..<100 {
            for denom in 10..<100 {

                var n = numer
                var d = denom

                var g = gcd(n, num2: d)
                if g != d {
                    n /= g
                    d /= g
                }

                let digits_n = String(numer).flatMap { Int(String($0)) }
                let digits_d = String(denom).flatMap { Int(String($0)) }

                if digits_n.count > 1 && digits_d.count > 1 {
                    if digits_n[0] != digits_n[1] && digits_d[0] != digits_d[1] {
                        if digits_n[0] == digits_d[1] || digits_n[1] == digits_d[0] {
                            if n != numer {
                                if (digits_n[1] == n && digits_d[0] == d) || (digits_n[0] == n && digits_d[1] == d) {

                                    sumNumer += numer
                                    sumDenom += denom
                                    print("HIT: \(numer) / \(denom)  ::  \(n) / \(d)")
                                }
                            }
                        }
                    }
                }
            }
        }


        if sumNumer > 0 && sumDenom > 0 {

            var g = gcd(sumNumer, num2: sumDenom)
            if g != sumDenom {
                sumNumer /= g
                sumDenom /= g

            }

            print("Digit Canceling Fractions: \(sumDenom)")

            //sumNumer


        }

    }



}


