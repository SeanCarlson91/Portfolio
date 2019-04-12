using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class DoorAnimationController : MonoBehaviour {

    public Animator m_anim;
    
    //Called when the game starts.
    private void Start()
    {
        m_anim = GetComponent<Animator>();
        
    }
    
    void OpenDoor()//This is called by a broadcast message.
    {
        
        m_anim.SetBool("ButtonPressed", true);
    }
}
