//
//  HelloWorldViewController.m
//  HelloWorld
//
//  Created by Heiko Vogel on 07.02.13.
//  Copyright (c) 2013 Heiko Vogel. All rights reserved.
//

#import "HelloWorldViewController.h"

@interface HelloWorldViewController ()

@end

@implementation HelloWorldViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)setGreeting:(id)sender {
    
    NSString *username = [[NSString alloc] initWithString:self.textField.text];
    
    if (username.length == 0)
        username = @"World";
    
    self.label.text = [[NSString alloc] initWithFormat:@"Hello, %@!", username];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
    
    if (self.textField == textField) {
        [textField resignFirstResponder];
        return YES;
    }
    
    return NO;
}

@end
