using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System.Collections;

public class MenuScript : MonoBehaviour
{
    
    public Canvas EscapeMenu;
    //public Button nextLevel;
    bool paused=false;

     void Start()
    {
        EscapeMenu.enabled = false;
       
        
    }
    void Update()
     {
        
         if (Input.GetKeyDown(KeyCode.Escape))
        {
            Debug.Log("Toggling pause");
            paused = TogglePause();
        }
     }
     
     void OnGUI()
     {
         if(paused==true)
         {
            EnableUI();
         }
        if (paused == false)
        {
            DisableUI();
        }
     }
     
     bool TogglePause()
     {
        Debug.Log("togglePause executing");

         if(Time.timeScale == 0f)
         {
            Debug.Log("timeScale is 0f");
             Time.timeScale = 1f;
            Debug.Log("Returning false");
             return(false);
         }
         else
         {
             Time.timeScale = 0f;
            Debug.Log("Returning true");
            return (true);    
         }
     }
  public void EnableUI()
    {
        Debug.Log("GUI Enabled.");
        EscapeMenu.enabled = true;
        //nextLevel.enabled = true;
    }
    public void DisableUI()
    {
        Debug.Log("GUI Disabled.");
        EscapeMenu.enabled = false;
        //nextLevel.enabled = true;
    }

    public void ResumeButton()
    {
        paused = false;
    }


}
