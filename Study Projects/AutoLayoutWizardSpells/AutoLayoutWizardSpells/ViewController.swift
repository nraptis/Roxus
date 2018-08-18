//
//  ViewController.swift
//  AutoLayoutWizardSpells
//
//  Created by Raptis, Nicholas on 7/31/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

///////////////////////////////////////
//              Header               //
//                                   //
///////////////////////////////////////
//                                   //
//  //////////////  //////////////   //
//  //          //  //          //   //
//  //          //  //          //   //
//  //          //  //          //   //
//  //          //  //          //   //
//  //////////////  //////////////   //
//           Main Content            //
//  //////////////  //////////////   //
//  //          //  //          //   //
//  //          //  //          //   //
//  //          //  //          //   //
//  //          //  //          //   //
//  //////////////  //////////////   //
//                                   //
///////////////////////////////////////
//              Footer               //
//        //    Button    //         //
///////////////////////////////////////


import UIKit

class ViewController: UIViewController {

    //If we know we're going to build these views with valid constraints,
    //we can use the empty constructor / initializer, which is uncommon.
    var toggleButton = UIButton()

    var header = UIView()
    var footer = UIView()

    var mainContent = UIView()

    var iv1 = UIImageView()
    var iv2 = UIImageView()
    var iv3 = UIImageView()
    var iv4 = UIImageView()

    var image1 = UIImage(named: "vader_1.png")
    var image2 = UIImage(named: "vader_3.jpg")
    var image3 = UIImage(named: "yoda_1.jpg")
    var image4 = UIImage(named: "yoda_2.png")

    var layoutConfig1 = [NSLayoutConstraint]()
    var layoutConfig2 = [NSLayoutConstraint]()

    var layoutMode: Int = 1

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.

        //Add all of our views as desired:
        view.addSubview(mainContent)
        view.addSubview(header)
        view.addSubview(footer)

        //image views go to main content...
        mainContent.addSubview(iv1)
        mainContent.addSubview(iv2)
        mainContent.addSubview(iv3)
        mainContent.addSubview(iv4)

        //button goes to footer.
        footer.addSubview(toggleButton)

        //Disable translatesAutoresizingMaskIntoConstraints on all items we want to manually constrain
        toggleButton.translatesAutoresizingMaskIntoConstraints = false
        footer.translatesAutoresizingMaskIntoConstraints = false
        mainContent.translatesAutoresizingMaskIntoConstraints = false
        header.translatesAutoresizingMaskIntoConstraints = false
        iv1.translatesAutoresizingMaskIntoConstraints = false
        iv2.translatesAutoresizingMaskIntoConstraints = false
        iv3.translatesAutoresizingMaskIntoConstraints = false
        iv4.translatesAutoresizingMaskIntoConstraints = false

        //H4xor beautiful styles.
        mainContent.layer.cornerRadius = 6.0
        mainContent.backgroundColor = #colorLiteral(red: 0.9259895035, green: 0.930837616, blue: 0.930837616, alpha: 1)
        mainContent.clipsToBounds = true

        //H4xor beautiful styles.
        header.backgroundColor = #colorLiteral(red: 0.501960814, green: 0.501960814, blue: 0.501960814, alpha: 1)
        header.layer.shadowOffset = CGSize(width: 0.0, height: 3.0)
        header.layer.shadowRadius = 6.666
        header.layer.shadowColor = #colorLiteral(red: 0.2549019754, green: 0.2745098174, blue: 0.3019607961, alpha: 1)
        header.layer.shadowOpacity = 0.666

        //H4xor beautiful styles.
        footer.backgroundColor = #colorLiteral(red: 0.501960814, green: 0.501960814, blue: 0.501960814, alpha: 1)
        footer.layer.shadowOffset = CGSize(width: 0.0, height: -3.0)
        footer.layer.shadowRadius = 6.666
        footer.layer.shadowColor = #colorLiteral(red: 0.2549019754, green: 0.2745098174, blue: 0.3019607961, alpha: 1)
        footer.layer.shadowOpacity = 0.666

        //Use "clever" emoji for title, this will make the users reel back in amazement.
        toggleButton.setTitle("🛠", for: .normal)
        toggleButton.titleLabel!.font = UIFont.systemFont(ofSize: 36)
        //Small hook for this button.
        toggleButton.addTarget(self, action: #selector(clickToggle(_:)), for: .touchUpInside)

        //Assign the images to the image views
        iv1.image = image1
        iv2.image = image2
        iv3.image = image3
        iv4.image = image4

        iv1.contentMode = .scaleAspectFill
        iv2.contentMode = .scaleAspectFill
        iv3.contentMode = .scaleAspectFill
        iv4.contentMode = .scaleAspectFill

        iv1.clipsToBounds = true
        iv2.clipsToBounds = true
        iv3.clipsToBounds = true
        iv4.clipsToBounds = true

        iv1.layer.cornerRadius = 6.666
        iv2.layer.cornerRadius = 6.666
        iv3.layer.cornerRadius = 6.666
        iv4.layer.cornerRadius = 6.666

        /////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////
        //                                                             //
        //  Constant constraints, that do not change as we re-arrange  //
        //                                                             //
        /////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////

        //Keep a list of all the static anchor constraints we make.
        var achors = [NSLayoutConstraint]()

        //Pin header to the top
        achors.append(header.leftAnchor.constraint(equalTo: view.leftAnchor, constant: 6.666))
        achors.append(header.rightAnchor.constraint(equalTo: view.rightAnchor, constant: -6.666))
        achors.append(header.topAnchor.constraint(equalTo: view.topAnchor, constant: 6.666))
        //Give the header a fixed height
        let headerHeightConstraint = NSLayoutConstraint(item: header, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 40.0)
        header.addConstraint(headerHeightConstraint)

        //Pin footer to the bottom
        achors.append(footer.leftAnchor.constraint(equalTo: view.leftAnchor, constant: 6.666))
        achors.append(footer.rightAnchor.constraint(equalTo: view.rightAnchor, constant: -6.666))
        achors.append(footer.bottomAnchor.constraint(equalTo: view.bottomAnchor, constant: -6.666))
        //Give the footer a fixed height
        let footerHeightConstraint = NSLayoutConstraint(item: footer, attribute: .height, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 40.0)
        footer.addConstraint(footerHeightConstraint)

        //Cram the main content between the header and footer...
        achors.append(mainContent.topAnchor.constraint(equalTo: header.bottomAnchor, constant: 6.666))
        achors.append(mainContent.bottomAnchor.constraint(equalTo: footer.topAnchor, constant: -6.666))
        achors.append(mainContent.leftAnchor.constraint(equalTo: view.leftAnchor, constant: 6.666))
        achors.append(mainContent.rightAnchor.constraint(equalTo: view.rightAnchor, constant: -6.666))

        //Center the toggle button inside the footer.
        achors.append(toggleButton.centerXAnchor.constraint(equalTo: footer.centerXAnchor, constant: 0.0))
        achors.append(toggleButton.centerYAnchor.constraint(equalTo: footer.centerYAnchor, constant: 0.0))

        //Toggle button gets a constant width.
        let buttonWidthConstraint = NSLayoutConstraint(item: toggleButton, attribute: .width, relatedBy: .equal, toItem: nil, attribute: .notAnAttribute, multiplier: 1.0, constant: 80.0)
        toggleButton.addConstraint(buttonWidthConstraint) //NOTICE: We add this constraint to BUTTON

        //Toggle button height, related to parent.
        let buttonHeightConstraint = NSLayoutConstraint(item: toggleButton, attribute: .height, relatedBy: .equal, toItem: footer, attribute: .height, multiplier: 1.0, constant: -6.0)
        footer.addConstraint(buttonHeightConstraint) //NOTICE: We add this constraint to FOOTER

        //Activate all of our anchors at once.
        NSLayoutConstraint.activate(achors)

        //Build up the constraints for configurtion #1
        generateConstraints1()

        //Build up the constraints for configurtion #2
        generateConstraints2()

        //By default we will go to configuration 2...
        //NSLayoutConstraint.activate(layoutConfig1)
        NSLayoutConstraint.activate(layoutConfig2)

    }

    override func viewWillTransition(to size: CGSize, with coordinator: UIViewControllerTransitionCoordinator) {

        if size.width < size.height {
            NSLayoutConstraint.deactivate(layoutConfig2)
            NSLayoutConstraint.activate(layoutConfig1)
            layoutMode = 0
        } else {

            NSLayoutConstraint.deactivate(layoutConfig1)
            NSLayoutConstraint.activate(layoutConfig2)
            layoutMode = 1
        }

        self.view.setNeedsLayout()
        coordinator.animate(alongsideTransition: { (context) in
            self.view.layoutIfNeeded()
        }) { (context) in
            print("Rotate Animation Complete...")
        }
    }

    func generateConstraints1() {

        //Layout the images in a vertical stack in the main view

        let heightPercent: CGFloat = 0.24
        let verticalSpacing: CGFloat = 3.0

        let im1ConHeight = NSLayoutConstraint(item: iv1, attribute: .height, relatedBy: .equal, toItem: mainContent, attribute: .height, multiplier: heightPercent, constant: 0.0)
        let im1ConCenterX = NSLayoutConstraint(item: iv1, attribute: .centerX, relatedBy: .equal, toItem: mainContent, attribute: .centerX, multiplier: 1.0, constant: 0.0)
        let im1ConTop = NSLayoutConstraint(item: iv1, attribute: .top, relatedBy: .equal, toItem: mainContent, attribute: .top, multiplier: 1.0, constant: verticalSpacing)
        let im1ConWidth = NSLayoutConstraint(item: iv1, attribute: .width, relatedBy: .equal, toItem: iv1, attribute: .height, multiplier: 1.25, constant: 0.0)
        mainContent.addConstraints([im1ConHeight, im1ConTop, im1ConCenterX])
        iv1.addConstraint(im1ConWidth)

        layoutConfig1.append(im1ConHeight)
        layoutConfig1.append(im1ConCenterX)
        layoutConfig1.append(im1ConTop)
        layoutConfig1.append(im1ConWidth)

        let im2ConHeight = NSLayoutConstraint(item: iv2, attribute: .height, relatedBy: .equal, toItem: mainContent, attribute: .height, multiplier: heightPercent, constant: 0.0)
        let im2ConCenterX = NSLayoutConstraint(item: iv2, attribute: .centerX, relatedBy: .equal, toItem: mainContent, attribute: .centerX, multiplier: 1.0, constant: 0.0)
        let im2ConTop = NSLayoutConstraint(item: iv2, attribute: .top, relatedBy: .equal, toItem: iv1, attribute: .bottom, multiplier: 1.0, constant: verticalSpacing)
        let im2ConWidth = NSLayoutConstraint(item: iv2, attribute: .width, relatedBy: .equal, toItem: iv2, attribute: .height, multiplier: 1.25, constant: 0.0)
        mainContent.addConstraints([im2ConHeight, im2ConTop, im2ConCenterX])
        iv2.addConstraint(im2ConWidth)

        layoutConfig1.append(im2ConHeight)
        layoutConfig1.append(im2ConCenterX)
        layoutConfig1.append(im2ConTop)
        layoutConfig1.append(im2ConWidth)

        let im3ConHeight = NSLayoutConstraint(item: iv3, attribute: .height, relatedBy: .equal, toItem: mainContent, attribute: .height, multiplier: heightPercent, constant: 0.0)
        let im3ConCenterX = NSLayoutConstraint(item: iv3, attribute: .centerX, relatedBy: .equal, toItem: mainContent, attribute: .centerX, multiplier: 1.0, constant: 0.0)
        let im3ConTop = NSLayoutConstraint(item: iv3, attribute: .top, relatedBy: .equal, toItem: iv2, attribute: .bottom, multiplier: 1.0, constant: verticalSpacing)
        let im3ConWidth = NSLayoutConstraint(item: iv3, attribute: .width, relatedBy: .equal, toItem: iv3, attribute: .height, multiplier: 1.25, constant: 0.0)
        mainContent.addConstraints([im3ConHeight, im3ConTop, im3ConCenterX])
        iv3.addConstraint(im3ConWidth)

        layoutConfig1.append(im3ConHeight)
        layoutConfig1.append(im3ConCenterX)
        layoutConfig1.append(im3ConTop)
        layoutConfig1.append(im3ConWidth)

        let im4ConHeight = NSLayoutConstraint(item: iv4, attribute: .height, relatedBy: .equal, toItem: mainContent, attribute: .height, multiplier: heightPercent, constant: 0.0)
        let im4ConCenterX = NSLayoutConstraint(item: iv4, attribute: .centerX, relatedBy: .equal, toItem: mainContent, attribute: .centerX, multiplier: 1.0, constant: 0.0)
        let im4ConTop = NSLayoutConstraint(item: iv4, attribute: .top, relatedBy: .equal, toItem: iv3, attribute: .bottom, multiplier: 1.0, constant: verticalSpacing)
        let im4ConWidth = NSLayoutConstraint(item: iv4, attribute: .width, relatedBy: .equal, toItem: iv4, attribute: .height, multiplier: 1.25, constant: 0.0)
        mainContent.addConstraints([im4ConHeight, im4ConTop, im4ConCenterX])
        iv4.addConstraint(im4ConWidth)

        layoutConfig1.append(im4ConHeight)
        layoutConfig1.append(im4ConCenterX)
        layoutConfig1.append(im4ConTop)
        layoutConfig1.append(im4ConWidth)

        NSLayoutConstraint.deactivate(layoutConfig1)
    }

    func generateConstraints2() {

        //Layout the images in a vertical stack in the main view

        let heightPercent: CGFloat = 0.48
        let widthPercent: CGFloat = 0.48

        let verticalSpacing: CGFloat = 3.0
        let horizontalSpacing: CGFloat = 5.0

        let im1ConLeft = NSLayoutConstraint(item: iv1, attribute: .left, relatedBy: .equal, toItem: mainContent, attribute: .left, multiplier: 1.0, constant: horizontalSpacing)
        let im1ConTop = NSLayoutConstraint(item: iv1, attribute: .top, relatedBy: .equal, toItem: mainContent, attribute: .top, multiplier: 1.0, constant: verticalSpacing)
        let im1ConHeight = NSLayoutConstraint(item: iv1, attribute: .height, relatedBy: .equal, toItem: mainContent, attribute: .height, multiplier: heightPercent, constant: 0.0)
        let im1ConWidth = NSLayoutConstraint(item: iv1, attribute: .width, relatedBy: .equal, toItem: mainContent, attribute: .width, multiplier: widthPercent, constant: 0.0)

        mainContent.addConstraints([im1ConLeft, im1ConTop, im1ConHeight, im1ConWidth])

        layoutConfig2.append(im1ConLeft)
        layoutConfig2.append(im1ConTop)
        layoutConfig2.append(im1ConHeight)
        layoutConfig2.append(im1ConWidth)

        let im2ConRight = NSLayoutConstraint(item: iv2, attribute: .right, relatedBy: .equal, toItem: mainContent, attribute: .right, multiplier: 1.0, constant: -horizontalSpacing)
        let im2ConTop = NSLayoutConstraint(item: iv2, attribute: .top, relatedBy: .equal, toItem: mainContent, attribute: .top, multiplier: 1.0, constant: verticalSpacing)
        let im2ConHeight = NSLayoutConstraint(item: iv2, attribute: .height, relatedBy: .equal, toItem: mainContent, attribute: .height, multiplier: heightPercent, constant: 0.0)
        let im2ConWidth = NSLayoutConstraint(item: iv2, attribute: .width, relatedBy: .equal, toItem: mainContent, attribute: .width, multiplier: widthPercent, constant: 0.0)

        mainContent.addConstraints([im2ConRight, im2ConTop, im2ConHeight, im2ConWidth])

        layoutConfig2.append(im2ConRight)
        layoutConfig2.append(im2ConTop)
        layoutConfig2.append(im2ConHeight)
        layoutConfig2.append(im2ConWidth)

        let im3ConLeft = NSLayoutConstraint(item: iv3, attribute: .left, relatedBy: .equal, toItem: mainContent, attribute: .left, multiplier: 1.0, constant: horizontalSpacing)
        let im3ConBottom = NSLayoutConstraint(item: iv3, attribute: .bottom, relatedBy: .equal, toItem: mainContent, attribute: .bottom, multiplier: 1.0, constant: -verticalSpacing)
        let im3ConHeight = NSLayoutConstraint(item: iv3, attribute: .height, relatedBy: .equal, toItem: mainContent, attribute: .height, multiplier: heightPercent, constant: 0.0)
        let im3ConWidth = NSLayoutConstraint(item: iv3, attribute: .width, relatedBy: .equal, toItem: mainContent, attribute: .width, multiplier: widthPercent, constant: 0.0)

        mainContent.addConstraints([im3ConLeft, im3ConBottom, im3ConHeight, im3ConWidth])

        layoutConfig2.append(im3ConLeft)
        layoutConfig2.append(im3ConBottom)
        layoutConfig2.append(im3ConHeight)
        layoutConfig2.append(im3ConWidth)

        let im4ConRight = NSLayoutConstraint(item: iv4, attribute: .right, relatedBy: .equal, toItem: mainContent, attribute: .right, multiplier: 1.0, constant: -horizontalSpacing)
        let im4ConBottom = NSLayoutConstraint(item: iv4, attribute: .bottom, relatedBy: .equal, toItem: mainContent, attribute: .bottom, multiplier: 1.0, constant: -verticalSpacing)
        let im4ConHeight = NSLayoutConstraint(item: iv4, attribute: .height, relatedBy: .equal, toItem: mainContent, attribute: .height, multiplier: heightPercent, constant: 0.0)
        let im4ConWidth = NSLayoutConstraint(item: iv4, attribute: .width, relatedBy: .equal, toItem: mainContent, attribute: .width, multiplier: widthPercent, constant: 0.0)

        mainContent.addConstraints([im4ConRight, im4ConBottom, im4ConHeight, im4ConWidth])

        layoutConfig2.append(im4ConRight)
        layoutConfig2.append(im4ConBottom)
        layoutConfig2.append(im4ConHeight)
        layoutConfig2.append(im4ConWidth)

        NSLayoutConstraint.deactivate(layoutConfig2)
    }

    @objc func clickToggle(_ sender: UIButton!) {
        if layoutMode == 1 {
            NSLayoutConstraint.deactivate(layoutConfig2)
            NSLayoutConstraint.activate(layoutConfig1)
            UIView.animate(withDuration: 0.666) {
                self.view.layoutIfNeeded()
            }
            layoutMode = 0
        } else {
            NSLayoutConstraint.deactivate(layoutConfig1)
            NSLayoutConstraint.activate(layoutConfig2)
            UIView.animate(withDuration: 0.666) {
                self.view.layoutIfNeeded()
            }
            layoutMode = 1
        }
    }
}

