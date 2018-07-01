//
//  SafeParser.h
//  NewNoiz
//
//  Created by Nick Raptis on 5/9/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "ModelDate.h"

@interface SafeParser : NSObject
{
    
}

+ (NSDictionary *)getDictionary:(NSDictionary *)pDictionary named:(NSString *)pName;
+ (NSString *)getString:(NSDictionary *)pDictionary named:(NSString *)pName;
+ (NSArray *)getArray:(NSDictionary *)pDictionary named:(NSString *)pName;

//- (ModelDate *)getDate:(NSDictionary *)pDictionary named:(NSString *)pName;
+ (float)getFloat:(NSDictionary *)pDictionary named:(NSString *)pName;
+ (int)getInt:(NSDictionary *)pDictionary named:(NSString *)pName;
+ (bool)getBool:(NSDictionary *)pDictionary named:(NSString *)pName;

@end
