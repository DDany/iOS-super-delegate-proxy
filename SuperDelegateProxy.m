//
//  SuperDelegateProxy.m
//  Proxy
//
//  Created by Zheng Wang on 13-2-19.
//  Copyright (c) 2013年 Dany. All rights reserved.
//

#import "SuperDelegateProxy.h"

@implementation SuperDelegateProxy

- (id)initWithReal:(id)real other:(id)other {

    realObject = real;
    otherObject = other;
    return self;
}

- (void)dealloc {
    realObject = nil;
    otherObject = nil;
}

- (NSMethodSignature *)methodSignatureForSelector:(SEL)sel {
    NSMethodSignature *signature;
    signature = [realObject methodSignatureForSelector:sel];
    if (signature) return signature;
    signature = [otherObject methodSignatureForSelector:sel];
    return signature;
}

- (void)forwardInvocation:(NSInvocation *)invocation {
    if (realObject && [realObject respondsToSelector:[invocation selector]]) [invocation invokeWithTarget:realObject];
    if (otherObject && [otherObject respondsToSelector:[invocation selector]]) [invocation invokeWithTarget:otherObject];
}

- (BOOL)respondsToSelector:(SEL)aSelector {
    if ([realObject respondsToSelector:aSelector]) return YES;
    if ([otherObject respondsToSelector:aSelector]) return YES;
    return NO;
}

#pragma mark - Getter
- (id)realProxy {
    return realObject;
}

#pragma mark - Setter
- (void)setRealProxy:(id)real {
    realObject = real;
}
@end
