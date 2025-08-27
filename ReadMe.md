# 食用指南 #
1. 将 TDXPlugin.dll 复制到 %通达信目录%\T0002\dlls\ 下
2. 重新登陆通达信
3. 在通达信的公式管理器中将TDXPlugin.dll绑定到第1号DLL
4. 新建一个条件选股公式，不需要额外参数, 代码如下：
<pre>
RET:=TDXDLL1(1,HIGH,CLOSE,VOL);
REF(RET,0)==1.0;
</pre>
