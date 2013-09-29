//
//  MyDocument.m
//  sketchometry
//
//  Created by Heiko Vogel on 25.02.13.
//  Copyright (c) 2013 DMI. All rights reserved.
//

#import "MyDocument.h"

@interface MyDocument ()
@end

@implementation MyDocument

- (id)contentsForType:(NSString *)typeName error:(NSError *__autoreleasing *)outError // the write routine
{
    return [_documentText dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)loadFromContents:(id)contents ofType:(NSString *)typeName error:(NSError *__autoreleasing *)outError // the load routine
{
    _documentText = [[NSString alloc] initWithData:contents encoding:NSUTF8StringEncoding];
    return ([contents length] > 0);
}

- (void)dealloc
{
    if (_documentText)
        [_documentText release];
    
    [super dealloc];
}

@end