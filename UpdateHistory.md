# 更新历史 #

## 2011.3.29 ##

开始计划Wiz保存文章到Google Code Wiki的项目，并付诸实施。

尝试解决wiki在网页上显示为乱码的问题，增加配置：

```
[defaults]
encoding=utf-8
```

没能解决问题。

把文件从ANSI转为UTF-8无BOM格式，乱码问题解决。

估计与hgrc配置无关，于是去掉了hgrc的utf-8设置。仍然是OK的。

## 把wiki放到Wiz中编辑 ##

首先找到Wiz插件中保存文章内容的办法。

通过hg\_commit从Wiz更新Wiki。

解决了空行有空白字符，结果wiki中不显示为换行的问题。

插入图片：

![http://wiki.sinojelly.googlecode.com/hg/images/save_button.jpg](http://wiki.sinojelly.googlecode.com/hg/images/save_button.jpg)

估计图片不会在GetText的时候获取到。采用什么方法才能得到什么地方插入了图片的信息呢？

## Wiz插件支持了设置wiki文件名等 ##

试试，看能否把新的内容正确更新上去。

commit对话框已修改，测试能否支持注释。

修改了一个函数找不到的问题。

修改了pluginPath找不到的问题。

发现注释不对，修改bat，再次测试。

发现注释参数传错，修改之。

修改了缺少.value的问题。

## 下一步计划 ##

  * 写菜单（支持提交、设置、预览）。
  * 在Wiz中使用wiki引擎浏览。
  * 图片的插入更方便。
  * 支持重新设置wiki参数。
  * 支持像分享一样，点击右边的小箭头，就可以显示更多菜单。（做不到）
  * 设置菜单样式、设置窗口、提交窗口样式，使得插件更美观。

## 问题 ##

  1. 为何GoCoWiki解析的结果没有换行了呢。（但官方提供的测试文件则有）
