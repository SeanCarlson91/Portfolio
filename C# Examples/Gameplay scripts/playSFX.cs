using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playSFX : MonoBehaviour {
    public AudioClip SFX1;
    AudioSource MyAudioSource;
	// Use this for initialization
	private void Start () {
        MyAudioSource = GetComponent<AudioSource>();
	}
	
    public void playMySFX()
    {
        MyAudioSource.clip = SFX1;
        MyAudioSource.Play();
    }
}
