//
//  STEDetailViewController.m
//  SimpleTextEditor
//
//  Created by Heiko Vogel on 14.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import "STEDetailViewController.h"

@interface STEDetailViewController ()
- (void)configureView;
@end

@implementation STEDetailViewController {
    STESimpleTextDocument *_document;
}

@synthesize detailItem = _detailItem;
@synthesize detailDescriptionLabel = _detailDescriptionLabel;

#pragma mark - Managing the detail item

- (void)configureView
{
    // Update the user interface for the detail item.

    if (self.detailItem) {
        self.detailDescriptionLabel.text = [self.detailItem description];
    }
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    [self configureView];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    // Clear out the text view contents.
    self.textView.text = @"";
    
    // Create the document and assign the delegate.
    _document = [[STESimpleTextDocument alloc] initWithFileURL:self.detailItem];
    _document.delegate = self;
    
    // If the file exists, open it; otherwise, create it.
    NSFileManager *fm = [NSFileManager defaultManager];
    
    if ([fm fileExistsAtPath:[self.detailItem path]])
        [_document openWithCompletionHandler:nil];
    else
        // Save the new document to disk.
        [_document saveToURL:self.detailItem 
            forSaveOperation:UIDocumentSaveForCreating
           completionHandler:^(BOOL success) {
               if (success)  {
                   NSLog(@"Saved to cloud");
               }  else {
                   NSLog(@"Failed to save to cloud");
               }
           }];
    
    // Register for keyboard notifications.
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
}

- (void)documentContentsDidChange:(STESimpleTextDocument *)document
{
    dispatch_async(dispatch_get_main_queue(), ^{
        self.textView.text = _document.documentText;
        NSLog(@"Loaded");
    });
}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    
    NSString* newText = self.textView.text;
    _document.documentText = newText;
    
    // Close the document.
    [_document closeWithCompletionHandler:nil];
    
    // Unregister keyboard notifications.
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillHideNotification object:nil];
}

- (void)keyboardWillShow:(NSNotification*)aNotification
{
   /* NSDictionary* info = [aNotification userInfo];
    
    CGRect kbSize = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue];
    
    double duration = [[info objectForKey:UIKeyboardAnimationDurationUserInfoKey] doubleValue];
    
    UIEdgeInsets insets = self.textView.contentInset;
    insets.bottom += kbSize.size.height;
    
    [UIView animateWithDuration:duration animations:^{
        self.textView.contentInset = insets;
    }];
*/
}

- (void)keyboardWillHide:(NSNotification*)aNotification
{
/*    NSDictionary* info = [aNotification userInfo];
    double duration = [[info objectForKey:UIKeyboardAnimationDurationUserInfoKey]
                       doubleValue];
    
    // Reset the text view's bottom content inset.
    UIEdgeInsets insets = self.textView.contentInset;
    insets.bottom = 0;
    
    [UIView animateWithDuration:duration animations:^{
        self.textView.contentInset = insets;
    }];
*/
}

@end
