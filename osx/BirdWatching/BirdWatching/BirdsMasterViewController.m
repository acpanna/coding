//
//  BirdsMasterViewController.m
//  BirdWatching
//
//  Created by Heiko Vogel on 08.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import "BirdsMasterViewController.h"

#import "BirdsDetailViewController.h"

#import "BirdSighting.h"
#import "BirdSightingDataController.h"

#import "AddSightingViewController.h"

@implementation BirdsMasterViewController

- (void)awakeFromNib
{
    [super awakeFromNib];
    self.dataController = [[BirdSightingDataController alloc] init];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.navigationItem.rightBarButtonItem.accessibilityHint = @"Adds a new bird-sighting event";
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}



#pragma mark - Table View

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.dataController countOfList];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"BirdSightingCell";
    static NSDateFormatter *formatter = nil;
    
    if (formatter == nil) {
        formatter = [[NSDateFormatter alloc] init];
        [formatter setDateStyle:NSDateFormatterMediumStyle];
    }
   
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier forIndexPath:indexPath];
    
    BirdSighting *sightingAtIndex = [self.dataController objectListAtIndex:indexPath.row];
    
    [[cell textLabel] setText:sightingAtIndex.name];
    [[cell detailTextLabel] setText:[formatter stringFromDate:sightingAtIndex.date]];
    
    return cell;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    return NO;
}

/////////////////////

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([[segue identifier] isEqualToString:@"showSightingDetails"]) {
        BirdsDetailViewController *detailViewController = [segue destinationViewController];
        detailViewController.sighting = [self.dataController objectListAtIndex:self.tableView.indexPathForSelectedRow.row];
    }
}

- (IBAction)done:(UIStoryboardSegue *)segue
{
    if ([[segue identifier] isEqualToString:@"ReturnInput"]) {
        
        AddSightingViewController *addController = [segue sourceViewController];
        
        if (addController.birdSighting) {
            [self.dataController addBirdSightingWithSighting:addController.birdSighting];
            [[self tableView] reloadData];
        }
        
        [self dismissViewControllerAnimated:YES completion:NULL];
    }
}

- (IBAction)cancel:(UIStoryboardSegue *)segue
{
    if ([[segue identifier] isEqualToString:@"CancelInput"]) {
        [self dismissViewControllerAnimated:YES completion:NULL];
    }
}

@end
