//
//  SuperDelegateProxy.h
//  Proxy
//
//  Created by Zheng Wang on 13-2-19.
//  Copyright (c) 2013年 Dany. All rights reserved.
//

#import <Foundation/Foundation.h>

/* =================================================================
    (Dany)此类用于解决一个问题:
    若 MJScrollView 继承自 UIScrollView, 设置MJScrollView的delegate时
    MJScrollView本身又在delegate方法中做一些附加操作, 而UIScrollView的delegate
    只能有一个, 所以使用代理实现.
 
    eg:
    一般情况下, 如上的例子中, 修改delegate的setter和getter方法如下:
 
    - (void)initDelegate {
        _proxy = [[SuperDelegateProxy alloc] initWithReal:nil other:self];
        [super setDelegate:(id <UIScrollViewDelegate>)_proxy];
    }

    - (void)setDelegate:(id<UIScrollViewDelegate>)delegate {
        _proxy.realProxy = delegate;
    }

    - (id<UIScrollViewDelegate>)delegate {
        return _proxy.realProxy;
    }

    - (void)dealloc {
        _proxy = nil;
        [super setDelegate:nil];
    }
  
    注意: 使用SuperDelegateProxy类的class不需要再遵循super的delegate protocol
    了,只需要直接实现delegate方法.
 
    eg:
    MJScrollView不需要再遵循 UIScrollViewDelegate, 直接实现
    - (void)scrollViewDidScroll:(UIScrollView *)scrollView;方法即可.
 ================================================================= */

@interface SuperDelegateProxy : NSProxy
{
    __weak id   realObject;
    
    // 一般情况下, otherObject都会是SuperDelegateProxy对象的所有者,所以为防止retain circle使用__weak.
    __weak id   otherObject;
}

- (id)initWithReal:(id)real other:(id)other;

- (id)realProxy;
- (void)setRealProxy:(id)real;
@end
