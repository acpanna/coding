//
//  FirstViewController.m
//  ColorAnimation
//
//  Created by Heiko Vogel on 05.04.13.
//  Copyright (c) 2013 DMI. All rights reserved.
//

#import "FirstViewController.h"

@interface FirstViewController ()

@end

@implementation FirstViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    [self setBackgroundColor];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc {
    [_redSlider release];
    [_greenSlider release];
    [_blueSlider release];
    [_hexLabel release];
    [super dealloc];
}

- (IBAction)redSliderMove:(id)sender {
    [self setBackgroundColor];
}

- (IBAction)greenSliderMove:(id)sender {
    [self setBackgroundColor];
}

- (IBAction)blueSlider:(id)sender {
    [self setBackgroundColor];
}

- (NSString *)generateHexStringWithRed:(double)redValue green:(double)greenValue blue:(double)blueValue {
    
    NSString *redString = [NSString stringWithFormat:@"%02x", (int) redValue];
    NSString *greenString = [NSString stringWithFormat:@"%02x", (int) greenValue];
    NSString *blueString = [NSString stringWithFormat:@"%02x", (int) blueValue];
    
    NSMutableString *hexString = [NSMutableString stringWithString:@"#"];
    
    [hexString appendString:redString];
    [hexString appendString:greenString];
    [hexString appendString:blueString];
    
    return hexString;
}

- (void)setBackgroundColor {
    
    float redValue = _redSlider.value;
    float greenValue = _greenSlider.value;
    float blueValue = _blueSlider.value;
    
    NSString *hexString = [self generateHexStringWithRed:redValue green:greenValue blue:blueValue];
    
    UIColor *bgColor = [UIColor colorWithRed:redValue/255.0 green:greenValue/255.0 blue:blueValue/255.0 alpha:1.0];
    
    [self.view setBackgroundColor:bgColor];
    
    [_hexLabel setText:hexString.uppercaseString];
}

@end
