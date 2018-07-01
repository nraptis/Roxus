//
//  SafeValidator.h
//  OptimizeRX
//
//  Created by Nicholas Raptis on 9/2/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface SafeValidator : NSObject
{
    
}

+ (BOOL)validateName:(NSString *)pString;

+ (BOOL)validateAddress:(NSString *)pString;
+ (BOOL)validateCity:(NSString *)pString;
+ (BOOL)validateState:(NSString *)pString;
+ (BOOL)validateZip:(NSString *)pString;

+ (BOOL)validateEmail:(NSString *)pString;
+ (BOOL)validatePhone:(NSString *)pString;

+ (BOOL)validateDateMMDDYYYY:(NSString *)pString;
+ (BOOL)validatePassword:(NSString *)pString;

@end



