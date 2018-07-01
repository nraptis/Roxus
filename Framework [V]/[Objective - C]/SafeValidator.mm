//
//  SafeValidator.m
//  OptimizeRX
//
//  Created by Nicholas Raptis on 9/2/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#import "SafeValidator.h"
//#import "FormUtils.h"

@implementation SafeValidator

+ (BOOL)validateName:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] > 1)
        {
            aReturn = YES;
        }
    }
    return aReturn;
}

+ (BOOL)validateAddress:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] > 0)
        {
            aReturn = YES;
        }
    }
    return aReturn;
}

+ (BOOL)validateCity:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] > 0)
        {
            aReturn = YES;
        }
    }
    return aReturn;
}


+ (BOOL)validateState:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] > 0)
        {
            aReturn = YES;
        }
    }
    return aReturn;
}


+ (BOOL)validateZip:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] >= 5)
        {
            aReturn = YES;
        }
    }
    return aReturn;
}

+ (BOOL)validateEmail:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] > 0)
        {
            NSString *aMailRegex =
            @"(?:[a-z0-9!#$%\\&'*+/=?\\^_`{|}~-]+(?:\\.[a-z0-9!#$%\\&'*+/=?\\^_`{|}"
            @"~-]+)*|\"(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21\\x23-\\x5b\\x5d-\\"
            @"x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])*\")@(?:(?:[a-z0-9](?:[a-"
            @"z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?|\\[(?:(?:25[0-5"
            @"]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-"
            @"9][0-9]?|[a-z0-9-]*[a-z0-9]:(?:[\\x01-\\x08\\x0b\\x0c\\x0e-\\x1f\\x21"
            @"-\\x5a\\x53-\\x7f]|\\\\[\\x01-\\x09\\x0b\\x0c\\x0e-\\x7f])+)\\])";
            NSPredicate *aMailTest = [NSPredicate predicateWithFormat:@"SELF MATCHES[c] %@", aMailRegex];
            if([aMailTest evaluateWithObject:pString])aReturn = YES;
        }
    }
    return aReturn;
}

+ (BOOL)validatePhone:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] > 8)
        {
            aReturn = YES;
        }
    }
    return aReturn;
}

+ (BOOL)validateDateMMDDYYYY:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] > 0)
        {
            aReturn = YES;
        }
    }
    return aReturn;
}

+ (BOOL)validatePassword:(NSString *)pString
{
    BOOL aReturn = NO;
    if(pString != nil)
    {
        if([pString length] > 0)
        {
            aReturn = YES;
        }
    }
    return aReturn;
}

@end
