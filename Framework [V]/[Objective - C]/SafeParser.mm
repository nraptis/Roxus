//
//  SafeParser.m
//  NewNoiz
//
//  Created by Nick Raptis on 5/9/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#import "SafeParser.h"

@implementation SafeParser

+ (NSDictionary *)getDictionary:(NSDictionary *)pDictionary named:(NSString *)pName
{
    NSDictionary *aReturn = nil;
    if((pDictionary != nil) && (pName != nil))
    {
        id aObject = [pDictionary objectForKey:pName];
        if(aObject != nil)
        {
            if([aObject isKindOfClass:[NSDictionary class]])
            {
                aReturn = (NSDictionary *)aObject;
            }
        }
    }
    return aReturn;
}

+ (NSString *)getString:(NSDictionary *)pDictionary named:(NSString *)pName
{
    NSString *aReturn = nil;
    if((pDictionary != nil) && (pName != nil))
    {
        id aObject = [pDictionary objectForKey:pName];
        if(aObject != nil)
        {
            if([aObject isKindOfClass:[NSNumber class]])
            {
                aReturn = [NSString stringWithFormat:@"%@", ((NSNumber *) aObject)];
            }
            else if([aObject isKindOfClass:[NSString class]])
            {
                aReturn = (NSString *)aObject;
            }
        }
    }
    return aReturn;
}

+ (NSArray *)getArray:(NSDictionary *)pDictionary named:(NSString *)pName
{
    NSArray *aReturn = nil;
    if((pDictionary != nil) && (pName != nil))
    {
        id aObject = [pDictionary objectForKey:pName];
        if(aObject != nil)
        {
            if([aObject isKindOfClass:[NSArray class]])
            {
                aReturn = (NSArray *)aObject;
            }
        }
    }
    return aReturn;
}

/*
- (ModelDate *)getDate:(NSDictionary *)pDictionary named:(NSString *)pName
{
    ModelDate *aReturn = [[ModelDate alloc] init];
    
    if(pDictionary != nil && pName != nil)
    {
        id aObject = [pDictionary objectForKey:pName];
        if(aObject != nil)
        {
            if([aObject isKindOfClass:[NSNumber class]])
            {
                aReturn = [[ModelDate alloc] initWithDouble:[((NSNumber *) aObject) doubleValue]];
            }
            else if([aObject isKindOfClass:[NSString class]])
            {
                aReturn = [[ModelDate alloc] initWithString:((NSString *)aObject)];
            }
        }
    }
    
    return aReturn;
}
*/

+ (float)getFloat:(NSDictionary *)pDictionary named:(NSString *)pName
{
    float aReturn = 0.0f;
    if(pDictionary != nil && pName != nil)
    {
        id aObject = [pDictionary objectForKey:pName];
        if(aObject != nil)
        {
            if([aObject isKindOfClass:[NSNumber class]])
            {
                aReturn = [((NSNumber *) aObject) floatValue];
            }
            else if([aObject isKindOfClass:[NSString class]])
            {
                aReturn = [((NSString *)aObject) floatValue];
            }
        }
    }
    return aReturn;
}

+ (bool)getBool:(NSDictionary *)pDictionary named:(NSString *)pName
{
    bool aReturn = false;
    if(pDictionary != nil && pName != nil)
    {
        id aObject = [pDictionary objectForKey:pName];
        if(aObject != nil)
        {
            if([aObject isKindOfClass:[NSNumber class]])
            {
                aReturn = [((NSNumber *) aObject) boolValue];
            }
            else if([aObject isKindOfClass:[NSString class]])
            {
                aReturn = [((NSString *)aObject) boolValue];
            }
        }
    }
    return aReturn;
}

+ (int)getInt:(NSDictionary *)pDictionary named:(NSString *)pName
{
    int aReturn = 0;
    if(pDictionary != nil && pName != nil)
    {
        id aObject = [pDictionary objectForKey:pName];
        if(aObject != nil)
        {
            if([aObject isKindOfClass:[NSNumber class]])
            {
                aReturn = [((NSNumber *) aObject) integerValue];
            }
            else if([aObject isKindOfClass:[NSString class]])
            {
                aReturn = [((NSString *)aObject) integerValue];
            }
        }
    }
    return aReturn;
}

@end
