package org.cocos2dx.hellojs;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.io.IOException;

public class HelloJS extends Activity {
    static private final String LOGTAG = "HelloJS";

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.d(LOGTAG, "onCreate");

        setContentView(R.layout.mainmenu);

        LinearLayout linearlayout = (LinearLayout) findViewById(R.id.mainmenu);

        addVersionStringsToLinearLayout(linearlayout);
        addScriptList(linearlayout);
    }

    static {
        System.loadLibrary("game");
    }

    private void addVersionStringsToLinearLayout(LinearLayout linearlayout) {
        TextView tv = new TextView(this);
        tv.setText(getLibVersions());
        linearlayout.addView(tv);
    }

    private void addScriptList(LinearLayout linearlayout) {
        String[] scripts = getJSAssets();
        for (String s: scripts) {
            Log.d(LOGTAG, "Script : " + s);
        }
    }

    private String[] getJSAssets() {
        try {
            AssetManager assets = getAssets();
            String[] assetList = assets.list("js");
            return assetList;
        } catch (java.io.IOException ioe) {
            Log.d(LOGTAG, "EXCEPTION! " + ioe);
            return (new String[] {""});
        }
    }

    private StringBuilder getLibVersions() {
        StringBuilder content = new StringBuilder();
        content.append("Hello Cocos, JS, Android!\n\n");
        try {
            content.append("Cocos2d Version = " + getCocosVersion() + "\n");
        } catch (Throwable t) {
            content.append("Error in Cocos2d");
        }

        try {
        content.append("JS VM Version = " + getJSVMVersion() + "\n");
        } catch (Throwable t) {
            content.append("Error in JavaScript VM");
        }

        try {
        content.append("Bindings Version = " + getBindingsVersion() + "\n");
        } catch (Throwable t) {
            content.append("Error in Cocos2d/JS Bindings");
        }

        return content;
    }

    private static native String getJSVMVersion();
    private static native void   jsvmDiagnostics();

    private static native String getBindingsVersion();
    private static native void   bindingsDiagnostics();

    private static native String getCocosVersion();
    private static native void   cocosDiagnostics();
}
