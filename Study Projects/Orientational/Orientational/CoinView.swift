//
//  CoinView.swift
//
//  Created by Raptis, Nicholas on 7/9/18.
//

import UIKit

class CoinView: UIView {

    var coinImageWidth: CGFloat = 128.0
    var coinImageHeight: CGFloat = 128.0
    
    var imageView1: UIImageView!
    var imageView2: UIImageView!

    var imageContent: UIView!

    var contentConstraintLeft: NSLayoutConstraint!
    var contentConstraintTop: NSLayoutConstraint!
    var contentConstraintWidth: NSLayoutConstraint!
    var contentConstraintHeight: NSLayoutConstraint!

    var iv1ConstraintLeft: NSLayoutConstraint!
    var iv1ConstraintTop: NSLayoutConstraint!
    var iv1ConstraintWidth: NSLayoutConstraint!
    var iv1ConstraintHeight: NSLayoutConstraint!

    var iv2ConstraintLeft: NSLayoutConstraint!
    var iv2ConstraintTop: NSLayoutConstraint!
    var iv2ConstraintWidth: NSLayoutConstraint!
    var iv2ConstraintHeight: NSLayoutConstraint!

    //Here we will just set up all of our constraints and local references,
    //our final layout will not be correct, but all the constraints will be
    //configured properly.
    func setUp(landscapeMode landscape: Bool, withVC vc: CoinViewController!) {

        coinImageWidth = vc.coinImage.size.width
        coinImageHeight = vc.coinImage.size.height

        imageContent = UIView()
        imageContent.translatesAutoresizingMaskIntoConstraints = false
        addSubview(imageContent)

        contentConstraintLeft = NSLayoutConstraint(item: imageContent, attribute: .left, relatedBy: .equal, toItem: self, attribute: .left, multiplier: 1.0, constant: 0.0)
        contentConstraintTop = NSLayoutConstraint(item: imageContent, attribute: .top, relatedBy: .equal, toItem: self, attribute: .top, multiplier: 1.0, constant: 0.0)
        contentConstraintWidth = NSLayoutConstraint(item: imageContent, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 256.0)
        contentConstraintHeight = NSLayoutConstraint(item: imageContent, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 128.0)
        addConstraints([contentConstraintLeft, contentConstraintTop])
        imageContent.addConstraints([contentConstraintWidth, contentConstraintHeight])

        imageView1 = UIImageView()
        imageView1.translatesAutoresizingMaskIntoConstraints = false
        imageView1.image = vc.coinImage
        imageContent.addSubview(imageView1)
        iv1ConstraintLeft = NSLayoutConstraint(item: imageView1, attribute: .left, relatedBy: .equal, toItem: imageContent, attribute: .left, multiplier: 1.0, constant: 0.0)
        iv1ConstraintTop = NSLayoutConstraint(item: imageView1, attribute: .top, relatedBy: .equal, toItem: imageContent, attribute: .top, multiplier: 1.0, constant: 0.0)
        iv1ConstraintWidth = NSLayoutConstraint(item: imageView1, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: coinImageWidth)
        iv1ConstraintHeight = NSLayoutConstraint(item: imageView1, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: coinImageHeight)
        addConstraints([iv1ConstraintLeft, iv1ConstraintTop])
        imageView1.addConstraints([iv1ConstraintWidth, iv1ConstraintHeight])
        
        imageView2 = UIImageView()
        imageView2.translatesAutoresizingMaskIntoConstraints = false
        imageView2.image = vc.coinImage
        imageContent.addSubview(imageView2)
        iv2ConstraintLeft = NSLayoutConstraint(item: imageView2, attribute: .left, relatedBy: .equal, toItem: imageContent, attribute: .left, multiplier: 1.0, constant: 0.0)
        iv2ConstraintTop = NSLayoutConstraint(item: imageView2, attribute: .top, relatedBy: .equal, toItem: imageContent, attribute: .top, multiplier: 1.0, constant: 0.0)
        iv2ConstraintWidth = NSLayoutConstraint(item: imageView2, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: coinImageWidth)
        iv2ConstraintHeight = NSLayoutConstraint(item: imageView2, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: coinImageHeight)
        addConstraints([iv2ConstraintLeft, iv2ConstraintTop])
        imageView2.addConstraints([iv2ConstraintWidth, iv2ConstraintHeight])
    }

    //Assuming "setUp" has already been called, we now layout for
    //our desired orientation. The beauty of this technique is that
    //"content" can be any size and contain any types of UI elements,
    //not only images.
    //
    //For landscape, we stack the images like so:
    //[I1][I2]
    //For portrait, we stack the images like so:
    //[I1]
    //[I2]
    //
    func layoutForSize(_ size: CGSize, landscapeMode landscape: Bool) {
        var totalWidth: CGFloat = coinImageWidth
        var totalHeight: CGFloat = coinImageHeight

        if landscape {
            iv2ConstraintLeft.constant = coinImageWidth
            totalWidth += coinImageWidth
        } else {
            iv2ConstraintTop.constant = coinImageHeight
            totalHeight += coinImageHeight
        }

        contentConstraintLeft.constant = -(totalWidth / 2.0)
        contentConstraintTop.constant = -(totalHeight / 2.0)

        contentConstraintWidth.constant = totalWidth
        contentConstraintHeight.constant = totalHeight

        imageContent.setNeedsLayout()

        //Now we fit this into the available space...
        //let sizeResult = size.getAspectFill(CGSize(width: totalWidth, height: totalHeight))
        //Switch to see different fitting behavior.
        let sizeResult = size.getAspectFit(CGSize(width: totalWidth, height: totalHeight))
        var transform = CGAffineTransform.identity
        transform = transform.translatedBy(x: size.width / 2.0, y: size.height / 2.0)
        transform = transform.scaledBy(x: sizeResult.scale, y: sizeResult.scale)
        imageContent.transform = transform

    }
}

