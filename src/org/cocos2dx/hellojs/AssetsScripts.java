package org.cocos2dx.hellojs;

import android.app.ListActivity;
import android.content.res.AssetManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;

/**
 * A list where the data for the list
 * comes from an array of strings.
 * The array of strings are the files in the
 * "assets/js" folder
 */
public class AssetsScripts extends ListActivity {
    static private final String LOGTAG = "AssetsScripts";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.d(LOGTAG, "onCreate");

        // map an array of strings to TextViews
        setListAdapter(new ArrayAdapter<String>(this,
                                                android.R.layout.simple_list_item_1,
                                                scriptList()));

        ListView lv = getListView();
        lv.setTextFilterEnabled(true);

        lv.setOnItemClickListener(new OnItemClickListener() {
                public void onItemClick(AdapterView<?> parent, View view,
                                        int position, long id) {
                    // When clicked, show a toast with the TextView text
                    Toast.makeText(getApplicationContext(), ((TextView) view).getText(),
                                   Toast.LENGTH_SHORT).show();
                }
            });
    }

    private String[] scriptList() {
        try {
            String[] scripts = getJSAssets();

            Log.d(LOGTAG, "Scripts :\n --- js/\n      |");
            for (String s: scripts) {
                Log.d(LOGTAG, "      +-- " + s);
            }

            return scripts;
        } catch (java.io.IOException ioe) {
            Log.d(LOGTAG, "Exception reading scripts from assets/js.\n" + ioe);
            return(new String[] {});
        }
    }

    private String[] getJSAssets() throws java.io.IOException {
        AssetManager assets = getAssets();
        String[] assetList = assets.list("js");
        return assetList;
    }
}
