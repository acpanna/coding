//
//  BirdsMasterViewController.h
//  BirdWatching
//
//  Created by Heiko Vogel on 08.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import <UIKit/UIKit.h>

@class BirdSightingDataController;

@interface BirdsMasterViewController : UITableViewController
@property (strong, nonatomic) BirdSightingDataController *dataController;

- (IBAction)cancel:(UIStoryboardSegue *)segue;
- (IBAction)done:(UIStoryboardSegue *)segue;

@end