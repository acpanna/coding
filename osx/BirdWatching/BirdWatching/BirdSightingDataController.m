//
//  BirdSightingDataController.m
//  BirdWatching
//
//  Created by Heiko Vogel on 11.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import "BirdSightingDataController.h"
#import "BirdSighting.h"

@interface BirdSightingDataController ()
-(void)initializeDefaultDataList;
@end

@implementation BirdSightingDataController

-(void)initializeDefaultDataList
{
    NSMutableArray *sightingList = [[NSMutableArray alloc] init];
    self.masterBirdSightingList = sightingList;
    
    NSDate *today = [NSDate date];
    BirdSighting *sighting = [[BirdSighting alloc] initWithName:@"Pigeon" location:@"Everywhere" date:today];
    
    [self addBirdSightingWithSighting:sighting];
}

-(void)setMasterBirdSightingList:(NSMutableArray *)newList
{
    if (_masterBirdSightingList != newList) {
        _masterBirdSightingList = [newList mutableCopy];
    }
}

-(id)init
{
    if (self = [super init]) {
        [self initializeDefaultDataList];
        return self;
    }
    
    return nil;
}

-(NSUInteger)countOfList
{
    return [self.masterBirdSightingList count];
}

-(BirdSighting *)objectListAtIndex:(NSUInteger)theIndex
{
    return [[self masterBirdSightingList] objectAtIndex:theIndex];
}

-(void)addBirdSightingWithSighting:(BirdSighting *)sighting
{
    [self.masterBirdSightingList addObject:sighting];
}

@end
