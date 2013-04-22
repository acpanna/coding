//
//  STEMasterViewController.h
//  SimpleTextEditor
//
//  Created by Heiko Vogel on 14.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface STEMasterViewController : UITableViewController

@property (weak, nonatomic) IBOutlet UIBarButtonItem *addButton;

- (IBAction)addDocument:(id)sender;

@end