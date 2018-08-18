//
//  BSTree.swift
//  Eulerz
//
//  Created by Raptis, Nicholas on 6/6/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

import UIKit

class BSTree: NSObject {
    
    required override init() {
        super.init()
    }
    
    var root: BSNode?

    func insert(value: Int) {
        
        if root == nil {
            root = BSNode(value)
            return
        } else {
            insert(root!, value)
        }
    }
    
    func insert(_ node: BSNode, _ value: Int) {
        
        if value < node.value {
            if node.left !== nil {
                insert(node.left!, value)
            } else {
                node.left = BSNode(value)
            }
        } else {
            if node.right !== nil {
                insert(node.right!, value)
            } else {
                node.right = BSNode(value)
            }
        }
    }
    
    func delete(value: Int) {
        root = delete(value, node: root)
    }
    
    func delete(_ value: Int, node: BSNode?) -> BSNode? {
        
        guard let n = node else {
            return nil
        }
        
        if value < n.value {
            n.left = delete(value, node: n.left)
        } else if value > n.value {
            n.right = delete(value, node: n.right)
        } else {
            if n.left == nil {
                return n.right
            } else if n.right == nil {
                return n.left
            } else {
                
                //left-mode node of right sub-tree..
                
                var minNode = (n.right)!
                while minNode.left !== nil {
                    minNode = (minNode.left)!
                }
                
                minNode.left = n.left
                return n.right
                
                
                
                
                //        5
                //   2         7
                //  1  4      6   8
                
                //           7
                //      6         8
                //    2
                //  1   4
                
                
                
            }
            
            
        }
        
        return node
    }
    
    
    func printData() {
        
        if root != nil {
            
            var nodeList = [BSNode]()
            var depthList = [Int]()
            var visitList = [Bool]()
            
            var output = ""
            
            var depth = 0
            depthList.append(0)
            nodeList.append(root!)
            visitList.append(false)
            
            while nodeList.count > 0 {
                
                let node = nodeList.remove(at: 0)
                let dep = depthList.remove(at: 0)
                let visit = visitList.remove(at: 0)
                
                if dep > depth {
                    depth += 1
                    output += "\n\n"
                }
                
                output += "[\(node.value)]"
                
                
                if node.left !== nil {
                    nodeList.append(node.left!)
                    depthList.append(depth + 1)
                    visitList.append(false)
                }
                
                if node.right !== nil {
                    nodeList.append(node.right!)
                    depthList.append(depth + 1)
                    visitList.append(false)
                    
                }
                
                
                
                
                //depth
            }
            
            
            print(output)
            
        }
    }
    
}
