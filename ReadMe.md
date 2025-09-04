# 食用指南 #
1. 将 TDXPlugin.dll 复制到 %通达信目录%\T0002\dlls\ 下
2. 重新登陆通达信
3. 在通达信的公式管理器中将TDXPlugin.dll绑定到第1号DLL
4. 新建一个条件选股公式，设置参数RATE,范围0.01~0.99，默认值0.99, 代码如下：
<pre>
TMP1:=TDXDLL1(100,2.5,10,4);
RET:=TDXDLL1(3,HIGH,CLOSE,VOL);
TMP2:=TDXDLL1(100,RATE,0,0);
RET2:=TDXDLL1(2,HIGH,LOW,CLOSE);
REF(RET,0)==1.0 AND REF(RET2,0)>=3.0;
</pre>
5. 新建一个盈亏比查看公式，代码如下,其中N1为预设参数，默认值0.99，表示止损百分比:
<pre>
NT:=TDXDLL1(100,N1,0,0);
TDXDLL1(2,HIGH,LOW,CLOSE) COLORRED;
</pre>
