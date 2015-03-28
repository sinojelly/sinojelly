# SaveWiki插件 #

这是一个在Wiz中写Google Code Wiki的小插件。

## 优势 ##

  1. 可以完整的记录文件的更新历史。（它天生使用到了hg/svn/git版本管理工具）
  1. 插入图片更方便。（Wiz中按通常的方法插入的图片，也会自动发布到服务器并插入Wiki页面）
  1. 样式与内容分离。（这也是wiki的优势，写作内容的时候，不必太多的去关注样式和排版）

> 本插件特别适合那些经常修改自己的文章，但删除某些内容时，又舍不得的人。用本文介绍的方式，每次提交都会把当前的状态记录到版本库，永远不会丢失。由于svn不支持离线提交，推荐使用hg或者git，即使不用网上的服务器，都可以使用本文介绍的方法把历史保存到本地的版本库。

## 特性 ##

  1. 设置Wiz文章对应的wiki文件名、本地版本库路径、服务器库路径、归档用的脚本。
  1. 自动保存.wiki文件，并更新到Google Code服务器。（如果用hg，即使不联网，也能更新到本地库，避免历史信息丢失）
  1. 预览Wiz中的符合wiki语法的文章。
  1. 按习惯的所见即所得的方式插入图片到Wiz文章，发布时图片自动发布到服务器，并能正确显示到Wiki页面上。

## 用法 ##

> 当然，首先是安装Wiz，然后根据下面步骤即可使用SaveWiki插件。

  1. 安装SaveWiki插件。

> 安装完成后，应该在编辑器上方的插件栏中增加了“保存+”按钮，参见下图：
<a href='Hidden comment: Picture added by Wiz2Wiki.'></a>
> ![http://wiki.sinojelly.googlecode.com/hg/images/Wiz2Wiki/14867924.png](http://wiki.sinojelly.googlecode.com/hg/images/Wiz2Wiki/14867924.png)

> 2) 在Wiz中以Google Code Wiki语法编辑文章。

> 3) 设置文章的wiki文件名等参数。（wiki文件名不能有中文、空格，可以有数字、下划线，必须以.wiki结尾）

> 点击“保存+”，弹出的菜单中点击“设置”，然后输入对应的参数。

> 例如我给本文设置的参数如下：
```
  Wiz2Wiki.wiki
  D:\Projects\Google\sinojelly-wiki
  http://wiki.sinojelly.googlecode.com/hg
  hg_commit.bat
```

> 参见下图：
<a href='Hidden comment: Picture added by Wiz2Wiki.'></a>
> ![http://wiki.sinojelly.googlecode.com/hg/images/Wiz2Wiki/16667334.png](http://wiki.sinojelly.googlecode.com/hg/images/Wiz2Wiki/16667334.png)

> 4) 提交。

> 点击“保存+”，再点击“提交”，输入comment，点击OK，即可提交到本地库，并更新到Google Code。（如果要支持svn、git，或者别的版本管理工具，增加几个commit cmd批处理即可）

> 5) 预览。

> 点击“保存+”，再点击“预览”，就会在Wiz中打开一个新的窗口，显示当前wiki文章的预览情况。

> 预览功能是用wikiwym开源项目提供的JavaScript版本的Google Code Wiki引擎实现的。当前预览的效果不如Google Code Wiki上的好看，甚至与wikiwym提供的测试文件相比，也差一些，欢迎内行的同学完善。

> 注意：预览是在一个Wiz的临时页面预览，无法使用批注功能。其实，Google Code Wiki的语法比较简单，不用wiki引擎渲染，可读性也是相当好的，我已经修改了“大纲”插件支持解析wiki的标题，现在阅读也非常方便了，参见下图：
<a href='Hidden comment: Picture added by Wiz2Wiki.'></a>
> ![http://wiki.sinojelly.googlecode.com/hg/images/Wiz2Wiki/4115571.png](http://wiki.sinojelly.googlecode.com/hg/images/Wiz2Wiki/4115571.png)

## TO DO ##

  1. 菜单、对话框美化。
  1. 本地预览功能的完善。（效果美化，支持本地预览图片显示等）

## 更新历史 ##

  1. 新增：支持方便的插入图片。（2011.4.1  v1.1）
  1. 修改：改进了菜单样式。（2011.4.3  v1.2）
  1. 修改：修正了存在非png格式的图片时弹出异常的问题。
  1. 修改：增加对jpg、jpeg、bmp、gif图片的支持。
  1. 修改：避免拷贝模板附带的文件（css/jpg等）到wiki发布目录。（2011.4.15 v1.3）

## FAQ ##

  * 为什么插入的图片未能复制到wiki目录？
  * 为什么Wiz模板的图片也复制到wiki目录？
  * [答] 上述两个问题都与Wiz文档相关的文件的处理方式有关。凡是带有“`[]`”的，都认为是模板的文件，不拷贝。

> Wiz打开文档ziw时，index\_files目录下存放的文件除了ziw文档自身插入的文件外，还有Wiz模板带有的css/jpg/png等文件。

> Wiz模板中带有的文件复制到wiki目录是毫无意义的，所以拷贝index\_files目录不太恰当。

> Wiz文档插入图片时的命名规则如下：
    1. 如果图片文件名带有中文，则用MD5转换为一串16进制数据，避免不识别的路径。
    1. 如果图片文件名不带中文，则直接使用该文件名。
    1. 如果是从剪贴板复制图片，则用数字命名。

> 由于上述第2种情况的存在，无法界定哪些文件名是文档的，所以采用排除模板附带文件的方法。

> 如果是修改网上的网页得到的模板，那么一般图片文件名中都有类似`[1]`这样的内容。参见下图：
<a href='Hidden comment: Picture added by Wiz2Wiki.'></a>
> ![http://wiki.sinojelly.googlecode.com/hg/images/Wiz2Wiki/16860806.png](http://wiki.sinojelly.googlecode.com/hg/images/Wiz2Wiki/16860806.png)

> 所以，最终我们选择“文件名中没有`[]`”的，就复制到wiki目录。

  * 怎样把Wiz编辑的wiki文章放到Google Code开源项目？
  * [答] 请参考如下步骤：
    1. 在Google Code上创建项目，并且选择hg版本管理工具
    1. 把wiki库通过hg clone取到本地：hg clonehttps://wiki.sinojelly.googlecode.com/hg/sinojelly-wiki --insecure
    1. 然后修改.hg/hgrc里面的defaults路径，把用户名、密码加进去。这是为了避免每次都输入密码。比如：https://username:password@wiki.sinojelly.googlecode.com/hg/
    1. 在文章的“保存+”的设置中设置正确的本地路径和远程路径。远程路径是为了在web上显示图片用的。
    1. 注意wiki文件名的命名，要符合Google Code的要求，只能有字母、数字、下划线等。

## 参考 ##

本软件已开源，欢迎有兴趣的同学去完善。

参考链接：

  * SaveWiki下载地址：http://cn.wizbrother.net/thread-6860-1-1.html
  * SaveWiki开源项目：https://bitbucket.org/sinojelly/wiz2wiki
  * SaveWiki文档网址：http://code.google.com/p/sinojelly/wiki/Wiz2Wiki
  * Wiz工具下载地址：http://www.wiz.cn/
  * wikiwym开源项目：http://code.google.com/p/wikiwym/
  * Google Code Wiki语法（中文）：http://code.google.com/p/chinese-room/wiki/WikiSyntax
  * Google Code Wiki语法（英文）：http://code.google.com/p/support/wiki/WikiSyntax
  * Wiz大纲插件（支持Wiki标题）：http://cn.wizbrother.net/thread-6971-1-1.html

## 鸣谢 ##

  * 感谢魏老师的耐心指点。
  * 感谢wikiwym开源项目提供的wiki引擎。
  * 感谢QQ网友“用户名被屏蔽”帮忙改进菜单样式。
