//
//  AddSightingViewController.m
//  BirdWatching
//
//  Created by Heiko Vogel on 11.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import "AddSightingViewController.h"

#import "BirdSighting.h"

@interface AddSightingViewController ()

@end

@implementation AddSightingViewController

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    if ((textField == self.birdNameInput) || (textField == self.locationInput)) {
        
        [textField resignFirstResponder];
        return YES;
    }
    
    return NO;
}

#pragma mark - Table view data source

#pragma mark - Table view delegate

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([[segue identifier] isEqualToString:@"ReturnInput"]) {
        
        if ([self.birdNameInput.text length] || [self.locationInput.text length]) {
            BirdSighting *sighting;
            NSDate *today = [NSDate date];
            
            sighting = [[BirdSighting alloc] initWithName:self.birdNameInput.text location:self.locationInput.text date:today];
            
            self.birdSighting = sighting;
        }
    }
}

@end
