//
//  BSNode.swift
//  Eulerz
//
//  Created by Raptis, Nicholas on 6/6/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

import UIKit

class BSNode: NSObject {
    
    convenience init(_ value: Int) {
        self.init()
        self.value = value
    }
    
    var right: BSNode?
    var left: BSNode?
    
    var value: Int = 0
    
}
