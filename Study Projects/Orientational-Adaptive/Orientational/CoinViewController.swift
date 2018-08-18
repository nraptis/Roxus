//
//  CoinViewController.swift
//
//  Created by Raptis, Nicholas on 7/9/18.
//

import UIKit

class CoinViewController: UIViewController {

    @IBOutlet weak var container: UIView!

    override func viewDidLoad() {
        super.viewDidLoad()

        //A container to help us see the edges & corners.
        container.clipsToBounds = true
        container.layer.cornerRadius = 10.0
        container.backgroundColor = UIColor(red: 0.98, green: 0.98, blue: 0.99, alpha: 1.0)
        container.layer.borderColor = UIColor(red: 0.66, green: 0.66, blue: 0.66, alpha: 1.0).cgColor
        container.layer.borderWidth = 0.5
    }
}
