//
//  HeapTwo.m
//  Quicksort
//
//  Created by Raptis, Nicholas on 12/6/16.
//  Copyright © 2016 company_name_goes_here. All rights reserved.
//

#import "HeapTwo.h"

@implementation HeapTwo


- (id)init {
    if (self = [super init] ) {
        
        data = (int *)malloc(5000);
        count = 0;
        
    }
    return self;
}

- (void)insert:(int)value {
    
    data[count] = value;
    count += 1;
    [self bubbleUp:count - 1];
}

- (int)pop {
    
    if(count > 0) {
        
        int result = data[0];
        data[0] = data[count - 1];
        count--;
        [self bubbleDown:0];
        return result;
    }
    
    return 0;
}

- (void)bubbleUp:(int)index {
    if (index > 0 && index < count) {
        
        int parentIndex = ((index - 1) / 2);
        
        while (index > 0) {
            if ((data[parentIndex] < data[index])) {
                int hold = data[parentIndex];
                data[parentIndex] = data[index];
                data[index] = hold;
                
                index = parentIndex;
                parentIndex = ((index - 1) / 2);
            } else {
                break;
            }
        }
    }
}

- (void)bubbleDown:(int)index {
    
    if (index >= 0 && index < count) {
        
        int maxIndex = index;
        
        while (true) {
            
            int leftChild = index * 2 + 1;
            int rightChild = index * 2 + 2;
            
            if (leftChild < count) {
                if (data[leftChild] > data[maxIndex]) {
                    maxIndex = leftChild;
                }
            }
            if (rightChild < count) {
                if(data[rightChild] > data[maxIndex]) {
                    maxIndex = rightChild;
                }
            }
            
            if (maxIndex == index) {
                break;
            } else {
                
                int hold = data[maxIndex];
                data[maxIndex] = data[index];
                data[index] = hold;
                
                index = maxIndex;
            }
        }
    }
}


@end







