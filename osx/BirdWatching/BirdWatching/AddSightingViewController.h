//
//  AddSightingViewController.h
//  BirdWatching
//
//  Created by Heiko Vogel on 11.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BirdSighting;

@interface AddSightingViewController : UITableViewController <UITextFieldDelegate>

@property (weak, nonatomic) IBOutlet UITextField *locationInput;
@property (weak, nonatomic) IBOutlet UITextField *birdNameInput;

@property (strong, nonatomic) BirdSighting *birdSighting;

@end