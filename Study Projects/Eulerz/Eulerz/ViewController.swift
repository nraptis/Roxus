//
//  ViewController.swift
//  Eulerz
//
//  Created by Raptis, Nicholas on 5/4/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        /*
        specialPythagoreanTriplet()
        largestProductInGrid()
        sumOfPrimesBelow2M()
        firstTriangleNumberWithOver500Divisors()
        largeSum()
        longestCollatzSequence()
        
        latticePaths()
        twoExponent1000DigitSum()
        
        countLettersInNumberStringsTo1000()
        maximumPathSumI()
        countSundaysIn20thCentury()
        factorialDigitSum()
        
        amicableNumbersTo10k()
        nonAbundantSums()
        millionthPermutationOf0to9()
        
        first1000DigitFibo()
        reciprocalCycles()
        */
        
        let tree = BSTree()
        tree.insert(value: 13)
        tree.insert(value: 14)
        tree.insert(value: 15)
        tree.insert(value: 10)
        tree.insert(value: 4)
        tree.insert(value: 5)
        tree.insert(value: 12)
        tree.insert(value: 20)
        tree.insert(value: 9)
        tree.insert(value: 6)
        tree.insert(value: 11)
        tree.insert(value: 5)
        tree.insert(value: 21)
        
        
        tree.printData()
        
        
        tree.delete(value: 13)
        print("======")
        tree.printData()
        
        
        tree.delete(value: 14)
        print("======")
        tree.printData()
        
        tree.delete(value: 15)
        print("======")
        tree.printData()
        
        tree.delete(value: 10)
        print("======")
        tree.printData()
        
        tree.delete(value: 4)
        print("======")
        tree.printData()
        
        
        tree.delete(value: 5)
        print("======")
        tree.printData()
        
        
        tree.delete(value: 12)
        print("======")
        tree.printData()
        
        
        tree.delete(value: 20)
        print("======")
        tree.printData()
        
        tree.delete(value: 9)
        print("======")
        tree.printData()
        
        tree.delete(value: 6)
        print("======")
        tree.printData()
        
        tree.delete(value: 11)
        print("======")
        tree.printData()
        
        tree.delete(value: 5)
        print("======")
        tree.printData()
        
        tree.delete(value: 21)
        print("======")
        tree.printData()
        
        print("======")
        tree.printData()
        
        
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    
    func amicableNumbersTo10k() {
        
        print("220 => \(sumOfAllProperDivisors(220))")
        print("284 => \(sumOfAllProperDivisors(284))")
        
        var divisorSums = [Int](repeating: 0, count: 10001)
        for i:Int in 1..<divisorSums.count {
            let sod = sumOfAllProperDivisors(i)
            divisorSums[i] = sod
        }
        
        var sumOfAmicable = 0
        for i:Int in 1..<divisorSums.count {
            let sod = divisorSums[i]
            if sod != i && sod < 10001 {
                if divisorSums[sod] == i {
                    sumOfAmicable += sod
                }
            }
        }
        print("sumOfAmicable = \(sumOfAmicable)")
    }
    
    func specialPythagoreanTriplet() {
        var c: Int = 1000
        for a: Int in 1..<500 {
            for b: Int in 1..<500 {
                var c = Int(sqrt(Double(a * a + b * b)))
                if a * a + b * b == c * c {
                    if a + b + c == 1000 {
                        print("Trip: \(a * b * c)")
                    }
                }
            }
        }
    }
    
    func countSundaysIn20thCentury() {
        
        let sundayIndex: Int = 6
        var dayIndex: Int = 0
        
        var year = 1900
        var month = 0
        
        var monthDayCount = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        
        var sundayCountDayOne = 0
        while true {
            let isLeapCentury = ((year % 100) == 0) && ((year % 400) != 0)
            let isLeapYear = ((year % 4) == 0) && (isLeapCentury == false)
            
            month = 0
            while month < 12 {
                var dayCount = monthDayCount[month]
                if month == 1 && isLeapYear {
                    dayCount = 29
                }
                
                for i: Int in 0..<dayCount {
                    if dayIndex == sundayIndex {
                        if year >= 1901 {
                            if i == 0 { sundayCountDayOne += 1 }
                        }
                        dayIndex = 0
                    } else { dayIndex += 1 }
                }
                month += 1
            }
            if year >= 2000 { break }
            year += 1
        }
        print("Day One Sundays in 21st century: \(sundayCountDayOne)")
    }
    
    func factorialDigitSum() {
        var finalResult = [1, 0, 0]
        for i: Int in 1..<100 {
            var digits = String(i).flatMap { Int(String($0)) }
            var result = longMultiply(int1: finalResult, int2: digits)
            finalResult = result
        }
        
        var sumOfDigits: Int = 0
        for i: Int in 0..<finalResult.count {
            sumOfDigits += finalResult[i]
        }
        
        print("Sum of 100! digits: \(sumOfDigits)")
        
    }
    
    func longMultiply(int1: [Int], int2: [Int]) -> [Int] {
        
        var longestNumberLength = int1.count
        if int2.count > longestNumberLength { longestNumberLength = int2.count }
        
        let resultMaxLength = (longestNumberLength + longestNumberLength)
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
        return trimmedResult
    }
    
    func maximumPathSumI() {
        maximumPathSum(fileName: "pyramid_1")
    }
    
    func maximumPathSum(fileName: String) {
        let filePath = Bundle.main.path(forResource: fileName, ofType: "txt")
        guard filePath != nil else {
            print("Avoid the C++ pyramid of doom with guard statement.")
            return
        }
        let fileURL = URL(fileURLWithPath: filePath!)
        do {
            let fileText = try String(contentsOf: fileURL, encoding: .utf8)
            let rowLines = fileText.split(separator: "\n")
            var pyramid = [[Int]]()
            var maxDepth = [[Int]]()
            for row in rowLines {
                let intLine = row.split(separator: " ").flatMap {
                    Int($0.trimmingCharacters(in: .whitespacesAndNewlines))
                }
                if intLine.count > 0 {
                    maxDepth.append(intLine)
                    pyramid.append(intLine)
                }
            }
            
            var depth: Int = pyramid.count - 1
            while depth >= 0 {
                var row = pyramid[depth]
                var mdRow = maxDepth[depth]
                if depth == pyramid.count - 1 {
                    //Bottom row gets copied over.
                    for col: Int in 0..<row.count { mdRow[col] = row[col] }
                } else {
                    var mdRowB = maxDepth[depth + 1]
                    for col: Int in 0..<row.count {
                        //Child "path" with highest sum.
                        let childMaxDepth: Int = max(mdRowB[col], mdRowB[col + 1])
                        //Plus the value of our current node.
                        maxDepth[depth][col] = row[col] + childMaxDepth
                    }
                    //Bang, here is our answer!
                    if depth == 0 { print("maximumPathSum: \(fileName) = \(maxDepth[0][0])") }
                }
                depth -= 1
            }
        } catch { /* T_T */ }
    }
    
    func stringToRow(_ text: String) -> [Int] {
        let result = text.split(separator: " ").flatMap {
            Int($0.trimmingCharacters(in: .whitespacesAndNewlines))
        }
        return result
    }
    
    func largestProductInGrid() {
        
        var grid = [[Int]]()
        grid.append(stringToRow("08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08"))
        grid.append(stringToRow("49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00"))
        grid.append(stringToRow("81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65"))
        grid.append(stringToRow("52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91"))
        grid.append(stringToRow("22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80"))
        grid.append(stringToRow("24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50"))
        grid.append(stringToRow("32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70"))
        grid.append(stringToRow("67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21"))
        grid.append(stringToRow("24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72"))
        grid.append(stringToRow("21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95"))
        grid.append(stringToRow("78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92"))
        grid.append(stringToRow("16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57"))
        grid.append(stringToRow("86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58"))
        grid.append(stringToRow("19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40"))
        grid.append(stringToRow("04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66"))
        grid.append(stringToRow("88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69"))
        grid.append(stringToRow("04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36"))
        grid.append(stringToRow("20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16"))
        grid.append(stringToRow("20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54"))
        grid.append(stringToRow("01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48"))
        let gridWidth: Int = grid[0].count
        let gridHeight: Int = grid.count
        var greatestProduct: Double = 0
        
        //horizontal
        for n: Int in 0..<gridHeight {
            
            for i: Int in 0..<(gridWidth - 4) {
                
                let product = Double(grid[i][n]) * Double(grid[i+1][n]) * Double(grid[i+2][n]) * Double(grid[i+3][n])
                if product > greatestProduct { greatestProduct = product }
            }
        }
        
        //vertical
        for n: Int in 0..<(gridHeight - 4) {
            for i: Int in 0..<gridWidth {
                let product = Double(grid[i][n]) * Double(grid[i][n+1]) * Double(grid[i][n+2]) * Double(grid[i][n+3])
                if product > greatestProduct { greatestProduct = product }
            }
        }
        
        //diagonal 1
        for n: Int in 0..<(gridHeight - 4) {
            for i: Int in 0..<(gridWidth - 4) {
                let product = Double(grid[i][n]) * Double(grid[i+1][n+1]) * Double(grid[i+2][n+2]) * Double(grid[i+3][n+3])
                if product > greatestProduct { greatestProduct = product }
            }
        }
        
        //diagonal 2 (The Tricky one - UP diagonals!!)
        for n: Int in 4..<gridHeight {
            for i: Int in 0..<(gridWidth - 4) {
                let product = Double(grid[i][n]) * Double(grid[i+1][n-1]) * Double(grid[i+2][n-2]) * Double(grid[i+3][n-3])
                if product > greatestProduct { greatestProduct = product }
            }
        }
        
        print("Greatest product: \(greatestProduct)")
    }
    
    func countLettersInNumberStringsTo1000() {
        
        var totalCharacterCount = 0
        for i: Int in 1..<1001 {
            var numberString = numberToString(i)
            numberString = numberString.replacingOccurrences(of: " ", with: "")
            
            totalCharacterCount += numberString.count
            
        }
        print("Total Chars (Number Words 1-1000) = \(totalCharacterCount)")
    }
    
    func numberToString(_ number: Int) -> String {
        if number >= 1000 { return "one thousand" }
        if number <= 0 { return "zero" }
        var result = ""
        var lowDigitWord = [String](repeating: "", count: 20)
        lowDigitWord[1] = "one"
        lowDigitWord[2] = "two"
        lowDigitWord[3] = "three"
        lowDigitWord[4] = "four"
        lowDigitWord[5] = "five"
        lowDigitWord[6] = "six"
        lowDigitWord[7] = "seven"
        lowDigitWord[8] = "eight"
        lowDigitWord[9] = "nine"
        lowDigitWord[10] = "ten"
        lowDigitWord[11] = "eleven"
        lowDigitWord[12] = "twelve"
        lowDigitWord[13] = "thirteen"
        lowDigitWord[14] = "fourteen"
        lowDigitWord[15] = "fifteen"
        lowDigitWord[16] = "sixteen"
        lowDigitWord[17] = "seventeen"
        lowDigitWord[18] = "eighteen"
        lowDigitWord[19] = "nineteen"
        
        var tensWords = [String](repeating: "", count: 10)
        tensWords[1] = "teen"
        tensWords[2] = "twenty"
        tensWords[3] = "thirty"
        tensWords[4] = "forty"
        tensWords[5] = "fifty"
        tensWords[6] = "sixty"
        tensWords[7] = "seventy"
        tensWords[8] = "eighty"
        tensWords[9] = "ninety"
        
        var num = number
        var hundredWord: String = ""
        if num >= 100 {
            let hundredDigit: Int = number / 100
            hundredWord = lowDigitWord[hundredDigit] + " hundred"
            num = num % 100
        }
        var teenWord: String = ""
        if num >= 20 {
            let teenDigit: Int = num / 10
            teenWord = tensWords[teenDigit]
            num = num % 10
        }
        var singleWord: String = ""
        if num > 0 { singleWord = lowDigitWord[num] }
        if hundredWord.count > 0 {
            result = hundredWord
            if teenWord.count > 0 || singleWord.count > 0 { result = "\(result) and " }
        }
        if teenWord.count > 0 {
            result = "\(result)\(teenWord)"
            if singleWord.count > 0 { result = "\(result) " }
        }
        if singleWord.count > 0 {
            result = "\(result)\(singleWord)"
        }
        return result
    }
    
    func largeSum() {
        var largeNumberList = [String]()
        largeNumberList.append("37107287533902102798797998220837590246510135740250")
        largeNumberList.append("46376937677490009712648124896970078050417018260538")
        largeNumberList.append("74324986199524741059474233309513058123726617309629")
        largeNumberList.append("91942213363574161572522430563301811072406154908250")
        largeNumberList.append("23067588207539346171171980310421047513778063246676")
        largeNumberList.append("89261670696623633820136378418383684178734361726757")
        largeNumberList.append("28112879812849979408065481931592621691275889832738")
        largeNumberList.append("44274228917432520321923589422876796487670272189318")
        largeNumberList.append("47451445736001306439091167216856844588711603153276")
        largeNumberList.append("70386486105843025439939619828917593665686757934951")
        largeNumberList.append("62176457141856560629502157223196586755079324193331")
        largeNumberList.append("64906352462741904929101432445813822663347944758178")
        largeNumberList.append("92575867718337217661963751590579239728245598838407")
        largeNumberList.append("58203565325359399008402633568948830189458628227828")
        largeNumberList.append("80181199384826282014278194139940567587151170094390")
        largeNumberList.append("35398664372827112653829987240784473053190104293586")
        largeNumberList.append("86515506006295864861532075273371959191420517255829")
        largeNumberList.append("71693888707715466499115593487603532921714970056938")
        largeNumberList.append("54370070576826684624621495650076471787294438377604")
        largeNumberList.append("53282654108756828443191190634694037855217779295145")
        largeNumberList.append("36123272525000296071075082563815656710885258350721")
        largeNumberList.append("45876576172410976447339110607218265236877223636045")
        largeNumberList.append("17423706905851860660448207621209813287860733969412")
        largeNumberList.append("81142660418086830619328460811191061556940512689692")
        largeNumberList.append("51934325451728388641918047049293215058642563049483")
        largeNumberList.append("62467221648435076201727918039944693004732956340691")
        largeNumberList.append("15732444386908125794514089057706229429197107928209")
        largeNumberList.append("55037687525678773091862540744969844508330393682126")
        largeNumberList.append("18336384825330154686196124348767681297534375946515")
        largeNumberList.append("80386287592878490201521685554828717201219257766954")
        largeNumberList.append("78182833757993103614740356856449095527097864797581")
        largeNumberList.append("16726320100436897842553539920931837441497806860984")
        largeNumberList.append("48403098129077791799088218795327364475675590848030")
        largeNumberList.append("87086987551392711854517078544161852424320693150332")
        largeNumberList.append("59959406895756536782107074926966537676326235447210")
        largeNumberList.append("69793950679652694742597709739166693763042633987085")
        largeNumberList.append("41052684708299085211399427365734116182760315001271")
        largeNumberList.append("65378607361501080857009149939512557028198746004375")
        largeNumberList.append("35829035317434717326932123578154982629742552737307")
        largeNumberList.append("94953759765105305946966067683156574377167401875275")
        largeNumberList.append("88902802571733229619176668713819931811048770190271")
        largeNumberList.append("25267680276078003013678680992525463401061632866526")
        largeNumberList.append("36270218540497705585629946580636237993140746255962")
        largeNumberList.append("24074486908231174977792365466257246923322810917141")
        largeNumberList.append("91430288197103288597806669760892938638285025333403")
        largeNumberList.append("34413065578016127815921815005561868836468420090470")
        largeNumberList.append("23053081172816430487623791969842487255036638784583")
        largeNumberList.append("11487696932154902810424020138335124462181441773470")
        largeNumberList.append("63783299490636259666498587618221225225512486764533")
        largeNumberList.append("67720186971698544312419572409913959008952310058822")
        largeNumberList.append("95548255300263520781532296796249481641953868218774")
        largeNumberList.append("76085327132285723110424803456124867697064507995236")
        largeNumberList.append("37774242535411291684276865538926205024910326572967")
        largeNumberList.append("23701913275725675285653248258265463092207058596522")
        largeNumberList.append("29798860272258331913126375147341994889534765745501")
        largeNumberList.append("18495701454879288984856827726077713721403798879715")
        largeNumberList.append("38298203783031473527721580348144513491373226651381")
        largeNumberList.append("34829543829199918180278916522431027392251122869539")
        largeNumberList.append("40957953066405232632538044100059654939159879593635")
        largeNumberList.append("29746152185502371307642255121183693803580388584903")
        largeNumberList.append("41698116222072977186158236678424689157993532961922")
        largeNumberList.append("62467957194401269043877107275048102390895523597457")
        largeNumberList.append("23189706772547915061505504953922979530901129967519")
        largeNumberList.append("86188088225875314529584099251203829009407770775672")
        largeNumberList.append("11306739708304724483816533873502340845647058077308")
        largeNumberList.append("82959174767140363198008187129011875491310547126581")
        largeNumberList.append("97623331044818386269515456334926366572897563400500")
        largeNumberList.append("42846280183517070527831839425882145521227251250327")
        largeNumberList.append("55121603546981200581762165212827652751691296897789")
        largeNumberList.append("32238195734329339946437501907836945765883352399886")
        largeNumberList.append("75506164965184775180738168837861091527357929701337")
        largeNumberList.append("62177842752192623401942399639168044983993173312731")
        largeNumberList.append("32924185707147349566916674687634660915035914677504")
        largeNumberList.append("99518671430235219628894890102423325116913619626622")
        largeNumberList.append("73267460800591547471830798392868535206946944540724")
        largeNumberList.append("76841822524674417161514036427982273348055556214818")
        largeNumberList.append("97142617910342598647204516893989422179826088076852")
        largeNumberList.append("87783646182799346313767754307809363333018982642090")
        largeNumberList.append("10848802521674670883215120185883543223812876952786")
        largeNumberList.append("71329612474782464538636993009049310363619763878039")
        largeNumberList.append("62184073572399794223406235393808339651327408011116")
        largeNumberList.append("66627891981488087797941876876144230030984490851411")
        largeNumberList.append("60661826293682836764744779239180335110989069790714")
        largeNumberList.append("85786944089552990653640447425576083659976645795096")
        largeNumberList.append("66024396409905389607120198219976047599490197230297")
        largeNumberList.append("64913982680032973156037120041377903785566085089252")
        largeNumberList.append("16730939319872750275468906903707539413042652315011")
        largeNumberList.append("94809377245048795150954100921645863754710598436791")
        largeNumberList.append("78639167021187492431995700641917969777599028300699")
        largeNumberList.append("15368713711936614952811305876380278410754449733078")
        largeNumberList.append("40789923115535562561142322423255033685442488917353")
        largeNumberList.append("44889911501440648020369068063960672322193204149535")
        largeNumberList.append("41503128880339536053299340368006977710650566631954")
        largeNumberList.append("81234880673210146739058568557934581403627822703280")
        largeNumberList.append("82616570773948327592232845941706525094512325230608")
        largeNumberList.append("22918802058777319719839450180888072429661980811197")
        largeNumberList.append("77158542502016545090413245809786882778948721859617")
        largeNumberList.append("72107838435069186155435662884062257473692284509516")
        largeNumberList.append("20849603980134001723930671666823555245252804609722")
        largeNumberList.append("53503534226472524250874054075591789781264330331690")
        
        var processList = [String]()
        var nextList = [String]()
        
        for string in largeNumberList {
            if string.count > 0 {
                processList.append(string)
            }
        }
        
        var overflow: Int = 0
        var runningSum: Int = 0
        var resultString = ""
        
        var reloop: Bool = true
        while reloop {
            reloop = false
            runningSum = overflow
            for string in processList {
                let last6 = substring(string: string, from: string.count - 6, to: string.count - 1)
                let firstChunk = substring(string: string, from: 0, to: string.count - 7)
                let number = Int(last6)!
                runningSum += number
                if firstChunk.count > 0 {
                    reloop = true
                    nextList.append(firstChunk)
                }
            }
            let appendValue = runningSum % 1000000
            overflow = runningSum / 1000000
            resultString = "\(appendValue)\(resultString)"
            processList.removeAll()
            for string in nextList {
                processList.append(string)
            }
            nextList.removeAll()
        }
        
        if overflow > 0 {
            let finalChunk = String(overflow)
            resultString = "\(finalChunk)\(resultString)"
        }
        print("Large Sum Result: \(resultString)")
    }
    
    func substring(string: String, from substringStartIndex: Int, to substringEndIndex: Int) -> String {
        var startIndex: Int = substringStartIndex
        var endIndex: Int = substringEndIndex
        if endIndex < 0 || startIndex >= string.count || endIndex < startIndex { return "" }
        if startIndex < 0 { startIndex = 0 }
        if endIndex > (string.count - 1) { endIndex = string.count - 1 }
        let si = string.index(string.startIndex, offsetBy: startIndex)
        let ei = string.index(string.startIndex, offsetBy: endIndex)
        let result = string[si...ei]
        return String(result)
    }
    
    func twoExponent1000DigitSum() {
        var digits = [Int](repeating: 0, count: 4096)
        var exponent: Int = 1
        digits[0] = 1
        var leftDigit: Int = 1
        while exponent <= 1000 {
            var carry: Int = 0
            for index: Int in 0..<(leftDigit + 1) {
                var value = digits[index] * 2 + carry
                carry = value / 10
                value = (value % 10)
                digits[index] = value
            }
            if carry > 0 {
                leftDigit += 1
                digits[leftDigit] = carry
            }
            exponent += 1
        }
        var sumOfDigits: Int = 0
        for i: Int in 0..<(leftDigit + 1) {
            sumOfDigits += digits[i]
        }
        
        print("Sum of Exponents: \(sumOfDigits)")
    }
    
    func latticePaths() {
        
        let gw: Int = 21
        let gh: Int = 21
        var lattice = [[Int]](repeating: [Int](repeating: 0, count: gh), count: gw)
        
        //Fill bottom with 1's
        for i: Int in 0..<(gw) {
            lattice[i][gh - 1] = 1
        }
        
        //Fill right with 1's
        for n: Int in 0..<(gh) {
            lattice[gw-1][n] = 1
        }
        
        //Dynamically populate lattice with known information.
        for inset: Int in 1..<gw {
            
            let passVer = (gh - 1) - inset
            let passHor = (gh - 1) - inset
            
            lattice[passHor][passVer] = (lattice[passHor + 1][passVer] + lattice[passHor][passVer + 1])
            
            var hor = passHor - 1
            var ver = passVer - 1
            
            while hor >= 0 {
                lattice[hor][passVer] = lattice[hor + 1][passVer] + lattice[hor][passVer + 1]
                hor -= 1
            }
            
            while ver >= 0 {
                lattice[passHor][ver] = lattice[passHor + 1][ver] + lattice[passHor][ver + 1]
                ver -= 1
            }
        }
        print("Lattice Paths: \(lattice[0][0])")
    }
    
    func longestCollatzSequence() {
        var sequenceLengthMemo = [Int](repeating: 0, count: 1000001)
        var checked = [Bool](repeating: false, count: 1000001)
        sequenceLengthMemo[1] = 1
        checked[1] = true
        var longestSequenceCount: Int = 1
        var longestSequenceStartingNumber: Int = 0
        for i: Int in 2..<1000001 {
            var reloop: Bool = true
            var value: Int = i
            var sequenceCount: Int = 1
            while reloop == true && value > 1 {
                if value < 1000000, checked[value] == true {
                    reloop = false
                    sequenceCount += (sequenceLengthMemo[value] - 1)
                } else {
                    sequenceCount += 1
                    if (value % 2 == 0) {
                        value = value / 2
                    } else {
                        value = value * 3 + 1
                    }
                }
            }
            sequenceLengthMemo[i] = sequenceCount
            checked[i] = true
            if sequenceCount > longestSequenceCount {
                longestSequenceStartingNumber = i
                longestSequenceCount = sequenceCount
            }
        }
        print("longestCollatzSequence Index: \(longestSequenceStartingNumber)")
    }
    
    
    func sumOfPrimesBelow2M() {
        
        var isNotPrime = [Bool](repeating: false, count: 2000000)
        var primeList = [Int]()
        for i: Int in 2..<2000000 {
            if isNotPrime[i] == true {
                continue
            }
            if isPrime(i) {
                var fillIndex: Int = i
                while fillIndex < 2000000 {
                    isNotPrime[fillIndex] = true
                    fillIndex += i
                }
                primeList.append(i)
            }
        }
        
        var sum = 0
        for i:Int in 0..<primeList.count {
            sum += primeList[i]
        }
        print("Sum of 1st 2 mil primes = \(sum)")
    }
    
    func firstTriangleNumberWithOver500Divisors() {
        var triNum: Int = 0
        var index: Int = 0
        while true {
            triNum += index
            var factors = numberOfFactors(triNum)
            if factors > 500 {
                print("Over 500: \(triNum)")
                break
            }
            index += 1
        }
    }
    
    func sumOfAllProperDivisors(_ number: Int) -> Int {
        if number <= 1 { return 1 }
        var result = 1
        let rootOfNumber = Int(sqrtf(Float(number)))
        var index: Int = 2
        while index <= rootOfNumber {
            if (number % index) == 0 {
                if (number / index) == index {
                    result += index
                } else {
                    result += index
                    result += (number / index)
                }
            }
            index += 1
        }
        return result
    }
    
    func numberOfFactors(_ number: Int) -> Int {
        if number <= 1 { return 1 }
        var result = 0
        let rootOfNumber = Int(sqrtf(Float(number)))
        var index: Int = 1
        while index <= rootOfNumber {
            if (number % index) == 0 {
                result += ((number / index) == index) ? 1 : 2
            }
            index += 1
        }
        return result
    }
    
    func isPrime(_ number: Int) -> Bool {
        if number <= 1 { return false }
        if number == 2 { return true }
        let limit = Int(sqrtf(Float(number))) + 1
        for i: Int in 2..<limit {
            if number % i == 0 { return false }
        }
        return true
    }
    
    
    func nonAbundantSums() {
        
        var magicNumber = 28124
        
        var sumOfDivisors = [Int](repeating: 0, count: magicNumber)
        var isAbundant = [Bool](repeating: false, count: magicNumber)
        
        
        for i: Int in 1..<magicNumber {
            sumOfDivisors[i] = sumOfAllProperDivisors(i)
            if sumOfDivisors[i] > i {
                isAbundant[i] = true
            }
            //print("i = \(i) sodd = \(sumOfAllProperDivisors(i))")
        }
        
        var finalSum: Int = 0
        for i: Int in 1..<magicNumber {
            
            var isSubOf2Abundants: Bool = false
            for j in 1..<i {
                
                if isAbundant[j] {
                    
                    var pairNumber = i - j
                    if isAbundant[pairNumber] == true {
                        isSubOf2Abundants = true
                        break
                    }
                    
                    
                    
                }
            }
            
            if isSubOf2Abundants {
                
            } else {
                finalSum += i
            }
        }
        print("Sum of all non-abundable-num: \(finalSum)")
    }
    
    func millionthPermutationOf0to9() {
        
        var str: String = "0123456789"
        
        var digits = str.flatMap { Int(String($0)) }
        
        var permutationList = [[Int]]()
        
        permute(arr: &digits, index: 0, result: &permutationList)
        
        //This is a slow-down...
        var permStrings = permutationList.map {
            $0.flatMap { String($0) }.joined(separator: "")
        }
        
        permStrings.sort { (a, b) -> Bool in
            a < b
        }
        
        print("Mil Permu Of 0-9: \(permStrings[999999])")
    }
    
    func permute(arr: inout [Int], index: Int, result: inout [[Int]]) {
        if index == arr.count - 1 {
            result.append(Array(arr))
        }
        for i: Int in index..<arr.count {
            var hold = arr[index]
            arr[index] = arr[i]
            arr[i] = hold
            permute(arr: &arr, index: index + 1, result: &result)
            hold = arr[index]
            arr[index] = arr[i]
            arr[i] = hold
        }
    }
    
    func trimLeadingZeroes(_ arr: [Int]) -> [Int] {
        var leftMostDigit: Int = arr.count - 1
        var resultIndex = arr.count - 1
        while resultIndex >= 0 {
            if arr[resultIndex] != 0 { leftMostDigit = resultIndex }
            resultIndex -= 1
        }
        let finalLength: Int = (arr.count - leftMostDigit)
        var trimmedResult = [Int](repeating: 0, count: finalLength)
        for i:Int in 0..<finalLength { trimmedResult[i] = arr[i + leftMostDigit] }
        return trimmedResult
    }
    
    func padZeroes(_ arr: [Int], _ length: Int) -> [Int] {
        if length > 0 {
            var result = [Int](repeating: 0, count: length)
            var resIndex = length - 1
            var index = arr.count - 1
            while resIndex >= 0 && index >= 0 {
                result[resIndex] = arr[index]
                resIndex -= 1
                index -= 1
            }
            return result
        } else {
            return [Int]()
        }
    }
    
    func first1000DigitFibo() {
        
        var fibPrev1 = [1]
        var fibPrev2 = [1]
        
        var res = [Int]()
        var fibIndex: Int = 1
        
        while res.count < 1000 {
            let num1 = trimLeadingZeroes(fibPrev1)
            let num2 = trimLeadingZeroes(fibPrev2)
            
            var operLen = num1.count
            if num2.count > operLen { operLen = num2.count }
            
            operLen += 2
            
            var carry = [Int](repeating: 0, count: operLen)
            var store = [Int](repeating: 0, count: operLen)
            var add1 = padZeroes(num1, operLen)
            var add2 = padZeroes(num2, operLen)
            var addIndex = operLen - 1
            
            while addIndex >= 0 {
                var sum = add1[addIndex] + add2[addIndex] + carry[addIndex]
                if sum > 10 {
                    if addIndex > 0 {
                        carry[addIndex - 1] = sum / 10
                    }
                    sum = sum % 10
                }
                store[addIndex] = sum
                addIndex -= 1
            }
            res = trimLeadingZeroes(store)
            fibIndex += 1
            fibPrev2 = fibPrev1
            fibPrev1 = res
        }
        print("First Fib Index 1000 Digits = \(fibIndex)")
    }
    
    func reciprocalCycles() {
        var denom = 2
        var largestCycleSize: Int = 0
        var bestAnswer: Int = 0
        while denom <= 1000 {
            
            //Perform long division as we learned in school.
            //"add zero, subtract, shift position"
            var numer = 1
            
            //Through guess-and-check, we make our output buffer ~5000 digits long...
            var result = [Int](repeating: 0, count: 5000)
            
            //implied that result[0] = whole number place... arbitrary...
            var slot = 0
            var ternimates: Bool = false
            
            while slot < result.count {
                if numer >= denom {
                    let digit = numer / denom
                    result[slot] = digit
                    numer = (numer - (digit * denom))
                    if numer == 0 {
                        //All 0's after this point. e.g. 1/100 = 0.00100000
                        ternimates = true
                        break
                    }
                } else {
                    //Add a zero, shift the output slot
                    numer *= 10
                    slot += 1
                }
            }
            
            //If it terminates, there's obviously no repeating cycle...
            if ternimates == false {
                
                //Brute force the solution.
                var cycleSize: Int = 0
  
                //We can have leading digits, e.g. 0.1666666 or 0.252323232323
                var leadingDigit: Int = 0
                
                //Assume a max of 10 leading digits?
                while leadingDigit < 10 {
                    var tryCycleSize: Int = 1
                    while tryCycleSize < (result.count / 2) + 1 {
                        var check1 = leadingDigit
                        var check2 = leadingDigit + tryCycleSize
                        var isCycle = true
                        while check1 < (leadingDigit + tryCycleSize) {
                            if check2 < result.count {
                                if result[check1] != result[check2] {
                                    isCycle = false
                                    break
                                }
                                check1 += 1
                                check2 += 1
                            } else {
                                isCycle = false
                                break
                            }
                        }
                        if isCycle {
                            cycleSize = tryCycleSize
                            break
                        }
                        tryCycleSize += 1
                    }
                    if cycleSize > largestCycleSize {
                        largestCycleSize = cycleSize
                        bestAnswer = denom
                    }
                    leadingDigit += 1
                }
            }
            denom += 1
        }
        
        print("Longest Repeating Div 1/1000 = \(bestAnswer)")
    }
}

