//
//  BirdSightingDataController.h
//  BirdWatching
//
//  Created by Heiko Vogel on 11.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BirdSighting;

@interface BirdSightingDataController : NSObject

@property (nonatomic, copy) NSMutableArray *masterBirdSightingList;

-(NSUInteger)countOfList;
-(BirdSighting *)objectListAtIndex:(NSUInteger)theIndex;
-(void)addBirdSightingWithSighting:(BirdSighting *)sighting;

@end
