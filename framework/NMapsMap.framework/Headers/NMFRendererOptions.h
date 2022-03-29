#import "NMFFoundation.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, NMFRendererType) {
    NMFRendererTypeOpenGL,
    NMFRendererTypeMetal
};

NMF_EXPORT
@interface NMFRendererOptions : NSObject

@property (class, nonatomic, readonly, nonnull) NMFRendererOptions *shared;
@property (nonatomic, assign) NMFRendererType rendererType;
@property (nonatomic, assign) BOOL msaa4x;

@end

NS_ASSUME_NONNULL_END
