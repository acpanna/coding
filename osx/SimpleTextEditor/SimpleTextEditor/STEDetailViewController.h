//
//  STEDetailViewController.h
//  SimpleTextEditor
//
//  Created by Heiko Vogel on 14.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "STESimpleTextDocument.h"

@interface STEDetailViewController : UIViewController <STESimpleTextDocumentDelegate>

@property (strong, nonatomic) NSURL* detailItem;

@property (weak, nonatomic) IBOutlet UILabel *detailDescriptionLabel;
@property (weak, nonatomic) IBOutlet UITextView *textView;

@end
