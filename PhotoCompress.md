Update：似乎Image Optimizer Professional的批量压缩更好，也能够不改变分辨率，保持图像品质默认好像70%，4M压缩后600多K，基本看不出图片质量损失。明天再学习一下它的用法，再验证一下。

# 完美的照片压缩存储方案 #

现在，很多家庭都有高像素的数码相机，如果家里有了宝宝，更是可能照了很多照片，它们占了很多硬盘空间，但不争气的硬盘还有可能出现故障，好好的照片可能就丢失了。为了解决这些问题，笔者进行了很多尝试，最终找到了自认为不错的解决方案，分享给大家。

## 工具选择 ##

选择标准：尽可能在压缩体积的时候，减少对质量的伤害。

对比了很多照片压缩工具，最终觉得JPEG Optimizer 和 Image Optimizer效果最好，压缩率高，压缩后的照片肉眼基本看不出差别。

这两个工具是一个公司出品的，看起来，是2006年左右就有的产品，后来没新版本，但经典就是经典。

下载地址：
http://www.xat.com/jpegopt/index.html

JPEG Optimizer的注册码：JS$28921 或 js$28921

## 压缩方法 ##

温馨提示：两种压缩方法都会去掉照片的EXIF信息，EXIF存储了照相的时间、光圈、快门等信息，摄影爱好者经常用它来学习相关技能，有些照片优化软件/照片打印机用它来自动优化照片显示效果。如果EXIF很重要，建议另外想办法。如果只是想保留照片的时间信息，可以用照片批量改名软件在文件名中加入拍照的时间，当然这个修改要在压缩之前完成。

### 方法一：用JPEG Optimizer进行近似无损的压缩（分辨率不变） ###

启动JPEG Optimizer程序，打开要压缩的文件，它就会进行压缩，在新的窗口显示压缩后的情况。压缩后的文件体积是压缩前的35%左右，照片分辨率没有缩小，质量损失也很小，即使放大到很大了看，也非常难以看出与原片的差异，放到极大的时候，才可能有一点点差异。

JPEG Optimizer采用什么算法达到这种压缩效果的不得而知，也许与“因色压缩”有关，也就是颜色少的地方多压缩。

参见下图：
<a href='Hidden comment: Picture added by Wiz2Wiki.'></a>
> ![http://wiki.sinojelly.googlecode.com/hg/images/PhotoCompress/49967151.png](http://wiki.sinojelly.googlecode.com/hg/images/PhotoCompress/49967151.png)

> 注：JPEG Optimizer的batch处理在Windows 7下不能运行，只能一张一张的压缩，稍微有点费事。

### 方法二：用Image Optimizer进行视觉一般感觉不出的高强度压缩（分辨率缩小） ###

选中要压缩的图片（可以是多张图片），点右键，选择“Optimize Here”，一会，就会生成压缩后的图片，原片文件名后增加“-Optimized”的就是。这种方法压缩后的图片体积很小，4M可以压缩到119K。

参见下图：
<a href='Hidden comment: Picture added by Wiz2Wiki.'></a>
> ![http://wiki.sinojelly.googlecode.com/hg/images/PhotoCompress/50780306.jpg](http://wiki.sinojelly.googlecode.com/hg/images/PhotoCompress/50780306.jpg)

原片和两种方法压缩后的文件对比如下，中间一个是方法一压缩后的情况，参见下图：
<a href='Hidden comment: Picture added by Wiz2Wiki.'></a>
> ![http://wiki.sinojelly.googlecode.com/hg/images/PhotoCompress/51181463.png](http://wiki.sinojelly.googlecode.com/hg/images/PhotoCompress/51181463.png)

## 实际压缩方案 ##

根据上面的情况，两种压缩方法各有所长，效果都很不错，为了尽可能避免好的照片有损压缩，同时尽可能缩小照片体积，不难得到如下的压缩方案：

  * 高质量的照片原样保存；（分级为5星）
  * 中等质量的照片基本无损压缩保存；（分级为4星）
  * 普通质量的照片压缩保存。（其它照片）

> 当然不值得保存的很差的照片，直接删除。

实际操作时，先对照片分级（Windows 7下直接在资源管理器中即可操作，XP可以安装Windows照片管理器），资源管理器中可以根据分级排序照片，之后就可以根据分级不同分别处理了。

Windows 7的资源管理器中设置照片分级的方法参见下图：
<a href='Hidden comment: Picture added by Wiz2Wiki.'></a>
> ![http://wiki.sinojelly.googlecode.com/hg/images/PhotoCompress/51956569.jpg](http://wiki.sinojelly.googlecode.com/hg/images/PhotoCompress/51956569.jpg)

> 注意：设置后需要保存，才会把设置的信息保存到照片中。

## 照片的存储 ##

本地磁盘并不可靠，磁盘坏的时候，很多数据都可能丢失，所以建议使用一种云存储工具备份数据到网络。

Dropbox是一个不错的选择：（注册地址：https://www.getdropbox.com/referrals/NTE4MTA3NDg5）
  * 自动同步，操作更方便；
  * 同步速度一流，设置不限速则更快；
  * 同步到Dropbox的Photos目录，还可以在WEB上使用Gallery方式浏览照片；
  * 照片可以外链；
  * 免费空间最大可以到20G。

> 注：
  1. 由于天朝网络的特殊性，WEB浏览和访问外链图片需要翻墙。照片同步不需要翻墙。
  1. 如果照片已经上传到服务器，之后才对照片进行压缩，那么同步后占用的Dropbox账户容量是否会减少，还有待验证。
