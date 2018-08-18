//
//  CoinViewController.swift
//
//  Created by Raptis, Nicholas on 7/9/18.
//

import UIKit

class CoinViewController: UIViewController {

    @IBOutlet weak var container: UIView!

    //"Single source of truth" instance of our expensive image file.
    var coinImage = UIImage(named: "btc.png")!

    //Portrait coin view + simple constraints.
    var coinViewPortrait: CoinView!
    var coinViewPortraitConstraintLeft: NSLayoutConstraint!
    var coinViewPortraitConstraintTop: NSLayoutConstraint!
    var coinViewPortraitConstraintWidth: NSLayoutConstraint!
    var coinViewPortraitConstraintHeight: NSLayoutConstraint!

    //Landscape coin view + simple constraints.
    var coinViewLandscape: CoinView!
    var coinViewLandscapeConstraintLeft: NSLayoutConstraint!
    var coinViewLandscapeConstraintTop: NSLayoutConstraint!
    var coinViewLandscapeConstraintWidth: NSLayoutConstraint!
    var coinViewLandscapeConstraintHeight: NSLayoutConstraint!

    var landscape: Bool = false

    var portraitWidth: CGFloat {
        if UIScreen.main.bounds.size.width > UIScreen.main.bounds.size.height {
            return UIScreen.main.bounds.size.height
        } else {
            return UIScreen.main.bounds.size.width
        }
    }

    var portraitHeight: CGFloat {
        if UIScreen.main.bounds.size.width > UIScreen.main.bounds.size.height {
            return UIScreen.main.bounds.size.width
        } else {
            return UIScreen.main.bounds.size.height
        }
    }

    var landscapeWidth: CGFloat {
        return portraitHeight
    }

    var landscapeHeight: CGFloat {
        return portraitWidth
    }

    var isDeviceLandscape: Bool {
        let orientation = UIApplication.shared.statusBarOrientation
        if orientation == .landscapeLeft || orientation == .landscapeRight { return true }
        return false
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        landscape = isDeviceLandscape

        //A container to help us see the edges & corners.
        container.clipsToBounds = true
        container.layer.cornerRadius = 10.0
        container.backgroundColor = UIColor(red: 0.98, green: 0.98, blue: 0.99, alpha: 1.0)
        container.layer.borderColor = UIColor(red: 0.66, green: 0.66, blue: 0.66, alpha: 1.0).cgColor
        container.layer.borderWidth = 0.5

        //Portrait
        coinViewPortrait = CoinView()
        coinViewPortrait.translatesAutoresizingMaskIntoConstraints = false
        container.addSubview(coinViewPortrait)
        coinViewPortraitConstraintLeft = NSLayoutConstraint(item: coinViewPortrait, attribute: .left, relatedBy: .equal, toItem: container, attribute: .left, multiplier: 1.0, constant: 0.0)
        coinViewPortraitConstraintTop = NSLayoutConstraint(item: coinViewPortrait, attribute: .top, relatedBy: .equal, toItem: container, attribute: .top, multiplier: 1.0, constant: 0.0)
        coinViewPortraitConstraintWidth = NSLayoutConstraint(item: coinViewPortrait, attribute: .width, relatedBy: .equal, toItem: container, attribute: .width, multiplier: 1.0, constant: 0.0)
        coinViewPortraitConstraintHeight = NSLayoutConstraint(item: coinViewPortrait, attribute: .height, relatedBy: .equal, toItem: container, attribute: .height, multiplier: 1.0, constant: 0.0)
        view.addConstraints([coinViewPortraitConstraintLeft, coinViewPortraitConstraintTop, coinViewPortraitConstraintWidth, coinViewPortraitConstraintHeight])


        //Landscape
        coinViewLandscape = CoinView()
        coinViewLandscape.translatesAutoresizingMaskIntoConstraints = false
        container.addSubview(coinViewLandscape)
        coinViewLandscapeConstraintLeft = NSLayoutConstraint(item: coinViewLandscape, attribute: .left, relatedBy: .equal, toItem: container, attribute: .left, multiplier: 1.0, constant: 0.0)
        coinViewLandscapeConstraintTop = NSLayoutConstraint(item: coinViewLandscape, attribute: .top, relatedBy: .equal, toItem: container, attribute: .top, multiplier: 1.0, constant: 0.0)
        coinViewLandscapeConstraintWidth = NSLayoutConstraint(item: coinViewLandscape, attribute: .width, relatedBy: .equal, toItem: container, attribute: .width, multiplier: 1.0, constant: 0.0)
        coinViewLandscapeConstraintHeight = NSLayoutConstraint(item: coinViewLandscape, attribute: .height, relatedBy: .equal, toItem: container, attribute: .height, multiplier: 1.0, constant: 0.0)
        view.addConstraints([coinViewLandscapeConstraintLeft, coinViewLandscapeConstraintTop, coinViewLandscapeConstraintWidth, coinViewLandscapeConstraintHeight])

        //First we do the one-time setup.
        coinViewPortrait.setUp(landscapeMode: false, withVC: self)
        coinViewLandscape.setUp(landscapeMode: true, withVC: self)

        //Now we do the layout update.
        coinViewPortrait.layoutForSize(CGSize(width: portraitWidth * 0.75, height: portraitHeight * 0.75), landscapeMode: false)
        coinViewLandscape.layoutForSize(CGSize(width: landscapeWidth * 0.75, height: landscapeHeight * 0.75), landscapeMode: true)

        //Finally, the first time we load, we need to show only the appropriate view.
        if landscape {
            coinViewPortrait.alpha = 0.0
        } else {
            coinViewLandscape.alpha = 0.0
        }
    }

    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {
        landscape = false
        if size.width > size.height { landscape = true }

        //Parent knows how to size the children..
        //Children do not change internal orientation or expected size...
        coinViewPortrait.layoutForSize(CGSize(width: portraitWidth * 0.75, height: portraitHeight * 0.75), landscapeMode: false)
        coinViewLandscape.layoutForSize(CGSize(width: landscapeWidth * 0.75, height: landscapeHeight * 0.75), landscapeMode: true)

        //Crossfade to the appropriate view based on orientation.
        coordinator.animate(alongsideTransition: { (coordinatorContext:UIViewControllerTransitionCoordinatorContext) in
            if self.landscape {
                self.coinViewPortrait.alpha = 0.0
                self.coinViewLandscape.alpha = 1.0
            } else {
                self.coinViewPortrait.alpha = 1.0
                self.coinViewLandscape.alpha = 0.0
            }

            //Pop the layouts inside the animation block.
            //Apple has done the grunt work in terms of making these puppies animate smoothly.
            self.coinViewPortrait.layoutIfNeeded()
            self.coinViewLandscape.layoutIfNeeded()
        }, completion: nil)
    }
    
}
