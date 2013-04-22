//
//  STESimpleTextDocument.h
//  SimpleTextEditor
//
//  Created by Heiko Vogel on 14.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol STESimpleTextDocumentDelegate;

@interface STESimpleTextDocument : UIDocument

@property (retain, nonatomic) NSString* documentText;
//@property (weak, nonatomic) id<STESimpleTextDocumentDelegate> delegate;
@property (retain, nonatomic) id<STESimpleTextDocumentDelegate> delegate;

@end

@protocol STESimpleTextDocumentDelegate <NSObject>
- (void)documentContentsDidChange:(STESimpleTextDocument*)document;
@end