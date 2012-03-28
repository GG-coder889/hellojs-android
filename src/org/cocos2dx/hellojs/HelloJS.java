package org.cocos2dx.hellojs;

import android.app.Activity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.io.IOException;

import org.cocos2dx.js.Bindings;

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

    private void addVersionStringsToLinearLayout(LinearLayout linearlayout) {
        TextView tv = new TextView(this);
        tv.setText(Bindings.getLibVersions());
        linearlayout.addView(tv);
    }

    private void addScriptList(LinearLayout linearlayout) {
        try {
            String[] scripts = getJSAssets();

            Log.d(LOGTAG, "Scripts :\n --- js/\n      |");
            for (String s: scripts) {
                Log.d(LOGTAG, "      +-- " + s);
            }

        } catch (java.io.IOException ioe) {
            Log.d(LOGTAG, "Exception reading scripts from assets/js.\n" + ioe);
            return;
        }
    }

    private String[] getJSAssets() throws java.io.IOException {
        AssetManager assets = getAssets();
        String[] assetList = assets.list("js");
        return assetList;
    }

    static {
        System.loadLibrary("game");
    }
}
