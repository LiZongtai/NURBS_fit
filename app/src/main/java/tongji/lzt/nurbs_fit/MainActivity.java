package tongji.lzt.nurbs_fit;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.Arrays;

import tongji.lzt.nurbs_fit.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    private ActivityMainBinding binding;

    float[] data=new float[]{5.0f,0.0f,4.0f,3.0f,3.0f,4.0f,0.0f,5.0f,-3.0f,4.0f,-4.0f,3.0f,-5.0f,0.0f,-4.0f,-3.0f,-3.0f,-4.0f,0.0f,-5.0f,3.0f,-4.0f,4.0f,-3.0f,5.0f,0.0f};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        NURBS_fit(data);
        DrawView view =findViewById(R.id.draw);
        view.invalidate();
        // Example of a call to a native method
//        TextView tv = binding.sampleText;
//        tv.setText(Arrays.toString( NURBS_fit(data)));
//        init();
    }

    private void init() {
        LinearLayout layout=(LinearLayout) findViewById(R.id.root);
        final DrawView view=new DrawView(this);
        //通知view组件重绘
        view.invalidate();
        layout.addView(view);

    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native float[] NURBS_fit(float[] pdata);
}