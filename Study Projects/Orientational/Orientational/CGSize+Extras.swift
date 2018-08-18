//
//  CGSize+Extras.swift
//
//  Created by Raptis, Nicholas on 10/17/16.
//

import UIKit

extension CGSize
{
    func getAspectFit(_ size: CGSize) -> (size: CGSize, scale: CGFloat) {
        var result = (size: CGSize(width: width, height: height), scale: CGFloat(1.0))
        if width > 0.1 && height > 0.1 && size.width > 0.1 && size.height > 0.1 {
            if (size.width / size.height) > (width / height) {
                result.scale = width / size.width
                result.size.width = width
                result.size.height = result.scale * size.height
            } else {
                result.scale = height / size.height
                result.size.width = result.scale * size.width
                result.size.height = height
            }
        }
        return result
    }
    
    func getAspectFill(_ size: CGSize) -> (size: CGSize, scale: CGFloat) {
        var result = (size: CGSize(width: width, height: height), scale: CGFloat(1.0))
        if width > 0.1 && height > 0.1 && size.width > 0.1 && size.height > 0.1 {
            if (size.width / size.height) < (width / height) {
                result.scale = width / size.width
                result.size.width = width
                result.size.height = result.scale * size.height
            } else {
                result.scale = height / size.height
                result.size.width = result.scale * size.width
                result.size.height = height
            }
        }
        return result
    }
}


