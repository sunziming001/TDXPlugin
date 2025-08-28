# 食用指南 #
1. 将 TDXPlugin.dll 复制到 %通达信目录%\T0002\dlls\ 下
2. 重新登陆通达信
3. 在通达信的公式管理器中将TDXPlugin.dll绑定到第1号DLL
4. 新建一个条件选股公式，不需要额外参数, 代码如下：
<pre>
RET:=TDXDLL1(1,HIGH,CLOSE,VOL);
RET2:=TDXDLL1(2,HIGH,LOW,CLOSE);   
REF(RET,0)==1.0 AND REF(RET2,0)>=3.0;
</pre>
5. 新建一个盈亏比查看公式，代码如下,其中N1为预设参数，表示止损百分比:
<pre>
NT:=TDXDLL1(100,N1,0,0);
TDXDLL1(2,HIGH,LOW,CLOSE) COLORRED;
</pre>
