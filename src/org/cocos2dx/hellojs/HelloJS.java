package org.cocos2dx.hellojs;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class HelloJS extends Activity {
    static private final String LOGTAG = "HelloJS";

    /** Called when the activity is first created. */
    @Override
        public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.d(LOGTAG, "onCreate");

        TextView tv = new TextView(this);

        StringBuilder content = new StringBuilder();
        content.append("Hello Cocos, JS, Android!\n\n");
        content.append("JS VM Version = " + getJSVMVersion() + "\n");
        content.append("Cocos2d Version = " + getCocosVersion() + "\n");
        content.append("Bindings Version = " + getBindingsVersion() + "\n");

        tv.setText(content);
        setContentView(tv);
    }

    static {
        System.loadLibrary("game");
    }

    private static native String getJSVMVersion();
    private static native void   jsvmDiagnostics();

    private static native String getBindingsVersion();
    private static native void   bindingsDiagnostics();

    private static native String getCocosVersion();
    private static native void   cocosDiagnostics();
}
