using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class mymusic : MonoBehaviour {

public AudioClip music1;
public AudioClip music2;

AudioSource myaudioSource;

    private void Start()
    {
        myaudioSource = GetComponent<AudioSource>();
        myaudioSource.clip = music1;
        myaudioSource.Play();
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("Player"))
        {
            if (myaudioSource != music2)
            myaudioSource.clip = music2;
            myaudioSource.Play();
        }
    }
   
}
