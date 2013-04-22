//
//  FirstViewController.h
//  ColorAnimation
//
//  Created by Heiko Vogel on 05.04.13.
//  Copyright (c) 2013 DMI. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface FirstViewController : UIViewController
@property (retain, nonatomic) IBOutlet UISlider *redSlider;
@property (retain, nonatomic) IBOutlet UISlider *greenSlider;
@property (retain, nonatomic) IBOutlet UISlider *blueSlider;
@property (retain, nonatomic) IBOutlet UILabel *hexLabel;

- (IBAction)redSliderMove:(id)sender;
- (IBAction)greenSliderMove:(id)sender;
- (IBAction)blueSlider:(id)sender;

-(void)setBackgroundColor;

@end
