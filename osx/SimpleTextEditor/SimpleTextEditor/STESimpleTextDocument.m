//
//  STESimpleTextDocument.m
//  SimpleTextEditor
//
//  Created by Heiko Vogel on 14.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import "STESimpleTextDocument.h"

@implementation STESimpleTextDocument

//@synthesize documentText = _documentText;
//@synthesize delegate = _delegate;

- (void)setDocumentText:(NSString *)newText {

    NSString *oldText = _documentText;
    _documentText = newText; //[newText copy];
    
    NSLog(@"setDCT called");
    
    // Register the undo operation ...
    
    [self.undoManager setActionName:@"Text Change"];
    [self.undoManager registerUndoWithTarget:self selector:@selector(setDocumentText:) object:oldText];
}

- (id)contentsForType:(NSString *)typeName error:(NSError *__autoreleasing *)outError { // the write routine

    if (!self.documentText)
        self.documentText = @"";
    
    NSLog(@"write called");
    
    NSData *docData = [_documentText dataUsingEncoding:NSUTF8StringEncoding];
    return docData;
}


- (BOOL)loadFromContents:(id)contents ofType:(NSString *)typeName error:(NSError *__autoreleasing *)outError { // the load routine

    if ([contents length] > 0)
        self.documentText = [[NSString alloc] initWithData:contents encoding:NSUTF8StringEncoding];
    else
        self.documentText = @"";
    
    NSLog(@"load called");
    
     // Tell the delegate that the document contents changed ...
    
    if (self.delegate && [self.delegate respondsToSelector:@selector(documentContentsDidChange:)])
        [self.delegate documentContentsDidChange:self];
    
    return YES;
}

@end
